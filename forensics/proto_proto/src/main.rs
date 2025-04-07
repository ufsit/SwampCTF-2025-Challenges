extern crate openssl;
extern crate serde;

use serde::{Deserialize, Serialize};
use std::env;
use std::fs;
use std::net::UdpSocket;
use std::path::{Path, PathBuf};

const BUFFER_SIZE: usize = 1024;
const HARD_CODED_KEY: &[u8] = b"super_secret_password";

#[derive(Serialize, Deserialize, Debug)]
enum Request {
    ListFiles = 0,
    EnterPassword = 1,
    DecryptFile = 2,
    RequestFile = 3,
}

#[derive(Serialize, Deserialize, Debug)]
enum Response {
    FileList = 0,
    PasswordAccepted = 1,
    PasswordRejected = 2,
    FileDecrypted = 3,
    DecryptionFailed = 4,
    InvalidRequest = 5,
    InvalidFilename = 6,
    FileData = 7,
}

fn xor_data(data: &mut [u8], key: &[u8]) {
    for (i, byte) in data.iter_mut().enumerate() {
        *byte ^= key[i % key.len()];
    }
}

fn handle_request(request_code: u8, data: &[u8], password: &mut Option<String>, encrypt_files: bool, base_dir: &Path) -> Vec<u8> {
    match request_code {
        0 => {
            println!("Handling ListFiles request");
            let paths: Vec<(u8, String)> = match fs::read_dir(base_dir) {
                Ok(entries) => entries.filter_map(|entry| {
                    entry.ok().and_then(|e| {
                        let path = e.path();
                        let file_type = if path.is_file() { 1 } else { 2 };
                        path.strip_prefix(base_dir).ok().and_then(|p| p.to_str().map(|s| (file_type, s.to_string())))
                    })
                }).collect(),
                Err(_) => return vec![Response::InvalidRequest as u8],
            };

            let mut response = vec![Response::FileList as u8];
            response.extend((paths.len() as u32).to_le_bytes().iter());

            for (file_type, path) in paths {
                response.push(file_type);
                let path_bytes = path.as_bytes();
                response.extend((path_bytes.len() as u32).to_le_bytes().iter());
                response.extend(path_bytes);
            }

            response
        }
        1 => {
            println!("Handling EnterPassword request");
            let pwd = match String::from_utf8(data.to_vec()) {
                Ok(pwd) => pwd,
                Err(_) => return vec![Response::InvalidRequest as u8],
            };
            if pwd == "super_secret_password" {
                *password = Some(pwd);
                vec![Response::PasswordAccepted as u8]
            } else {
                vec![Response::PasswordRejected as u8]
            }
        }
        2 => {
            println!("Handling RequestFile request");
            let mut offset = 0;
            let key = if encrypt_files {
                if data.len() < 1 {
                    println!("Invalid Request: data length too short for key length");
                    return vec![Response::InvalidRequest as u8];
                }
                let key_len = data[0] as usize;
                if data.len() < 1 + key_len {
                    println!("Invalid Request: data length too short for key");
                    return vec![Response::InvalidRequest as u8];
                }
                let key = &data[1..1 + key_len];
                offset = 1 + key_len;
                Some(key)
            } else {
                None
            };

            if data.len() <= offset {
                println!("Invalid Request: data length too short for filename length");
                return vec![Response::InvalidRequest as u8];
            }

            let filename_len = data[offset] as usize;
            offset += 1;
            if data.len() < offset + filename_len {
                println!("Invalid Request: data length too short for filename");
                return vec![Response::InvalidRequest as u8];
            }
            let filename = match String::from_utf8(data[offset..offset + filename_len].to_vec()) {
                Ok(filename) => filename,
                Err(_) => return vec![Response::InvalidRequest as u8],
            };
            let filepath = base_dir.join(&filename);
            if !is_valid_filename(&filepath, base_dir) {
                return vec![Response::InvalidFilename as u8];
            }

            let mut file_data = match fs::read(filepath) {
                Ok(data) => data,
                Err(_) => return vec![Response::InvalidFilename as u8],
            };
            if encrypt_files {
                xor_data(&mut file_data, HARD_CODED_KEY);
                if let Some(key) = key {
                    xor_data(&mut file_data, key);
                }
            }

            let mut response = vec![Response::FileData as u8];
            response.extend(file_data);
            response
        }
        _ => {
            println!("Invalid Request Code: {}", request_code);
            vec![Response::InvalidRequest as u8]
        },
    }
}

fn is_valid_filename(filepath: &Path, base_dir: &Path) -> bool {
    if filepath.components().any(|comp| matches!(comp, std::path::Component::ParentDir)) {
        return false;
    }
    if !filepath.starts_with(base_dir) || !filepath.is_file() {
        return false;
    }
    true
}

fn main() {
    println!("Starting server...");

    let args: Vec<String> = env::args().collect();
    if args.len() != 2 {
        eprintln!("Usage: {} <directory>", args[0]);
        std::process::exit(1);
    }
    let base_dir = PathBuf::from(&args[1]);
    if !base_dir.is_dir() {
        eprintln!("Error: {} is not a valid directory", args[1]);
        std::process::exit(1);
    }

    let socket = UdpSocket::bind("0.0.0.0:34254").expect("Couldn't bind to address");
    println!("Server is running on 0.0.0.0:34254");

    let encrypt_files = env::var("ENCRYPT_FILES").is_ok();
    if encrypt_files {
        println!("File encryption is enabled.");
    } else {
        println!("File encryption is disabled.");
    }

    let mut buf = [0; BUFFER_SIZE];
    let mut password: Option<String> = None;

    loop {
        let (amt, src) = match socket.recv_from(&mut buf) {
            Ok((amt, src)) => (amt, src),
            Err(_) => continue,
        };
        println!("Received data from {}", src);

        if amt < 1 {
            continue;
        }

        let request_code = buf[0];
        let data = &buf[1..amt];

        println!("Request Code: {}", request_code);
        println!("Data Length: {}", data.len());

        let response = handle_request(request_code, data, &mut password, encrypt_files, &base_dir);
        match socket.send_to(&response, &src) {
            Ok(_) => println!("Response sent to {}", src),
            Err(_) => println!("Failed to send response to {}", src),
        }
    }
}
