extern crate openssl;
extern crate serde;

use serde::{Deserialize, Serialize};
use std::env;
use std::io::{self, Write};
use std::net::UdpSocket;

const BUFFER_SIZE: usize = 1024;

enum RequestType {
    ListFiles,
    RequestFile,
    EnterPassword,
    Exit,
}

fn main() {
    let args: Vec<String> = env::args().collect();
    
    if args.len() < 3 {
        eprintln!("Usage: {} <host> <port>", args[0]);
        std::process::exit(1);
    }
    
    let server_addr = format!("{}:{}", args[1], args[2]);
    println!("Connecting to: {}", server_addr);
    
    let socket = UdpSocket::bind("0.0.0.0:0").expect("Couldn't bind to address");
    socket.connect(&server_addr).expect("Couldn't connect to server");

    loop {
        match get_user_choice() {
            RequestType::ListFiles => list_files(&socket),
            RequestType::RequestFile => request_file(&socket),
            RequestType::EnterPassword => enter_password(&socket),
            RequestType::Exit => break,
        }
    }
}

fn get_user_choice() -> RequestType {
    println!("Choose an option:");
    println!("1. List files");
    println!("2. Request a file");
    println!("3. Enter password");
    println!("4. Exit");

    print!("Enter your choice: ");
    io::stdout().flush().unwrap();

    let mut choice = String::new();
    io::stdin().read_line(&mut choice).unwrap();
    match choice.trim().parse::<u8>().unwrap_or(0) {
        1 => RequestType::ListFiles,
        2 => RequestType::RequestFile,
        3 => RequestType::EnterPassword,
        4 => RequestType::Exit,
        _ => {
            println!("Invalid choice. Please try again.");
            get_user_choice()
        }
    }
}

fn list_files(socket: &UdpSocket) {
    let request_code: u8 = 0;
    socket.send(&[request_code]).expect("Couldn't send data");

    let mut buf = [0; BUFFER_SIZE];
    let (amt, _src) = socket.recv_from(&mut buf).expect("Didn't receive data");

    if amt < 5 {
        println!("Invalid response received");
        return;
    }

    let response_code = buf[0];
    if response_code != 0 {
        println!("Unexpected response code: {}", response_code);
        return;
    }

    let num_entries = u32::from_le_bytes(buf[1..5].try_into().unwrap()) as usize;
    println!("Number of entries: {}", num_entries);

    let mut offset = 5;
    for _ in 0..num_entries {
        let entry_type = buf[offset];
        offset += 1;
        let entry_len = u32::from_le_bytes(buf[offset..offset + 4].try_into().unwrap()) as usize;
        offset += 4;
        let entry_name = String::from_utf8(buf[offset..offset + entry_len].to_vec()).unwrap();
        offset += entry_len;
        let entry_type_str = if entry_type == 1 { "File" } else { "Directory" };
        println!("{}: {}", entry_type_str, entry_name);
    }
}

fn request_file(socket: &UdpSocket) {
    print!("Enter the filename to request: ");
    io::stdout().flush().unwrap();

    let mut filename = String::new();
    io::stdin().read_line(&mut filename).unwrap();
    let filename = filename.trim().as_bytes().to_vec();

    let encrypt_files = env::var("ENCRYPT_FILES").is_ok();
    let mut request = vec![2]; // RequestFile code

    if encrypt_files {
        print!("Enter the key: ");
        io::stdout().flush().unwrap();

        let mut key = String::new();
        io::stdin().read_line(&mut key).unwrap();
        let key = key.trim().as_bytes().to_vec();

        request.push(key.len() as u8);
        request.extend(&key);
    }

    request.push(filename.len() as u8);
    request.extend(&filename);

    socket.send(&request).expect("Couldn't send data");

    let mut buf = [0; BUFFER_SIZE];
    let (amt, _src) = socket.recv_from(&mut buf).expect("Didn't receive data");

    let response_code = buf[0];
    if response_code != 7 {
        println!("Unexpected response code: {}", response_code);
        return;
    }

    let file_data = &buf[1..amt];
    match String::from_utf8(file_data.to_vec()) {
        Ok(file_string) => println!("Received file data: {}", file_string),
        Err(_) => println!("Received file data (bytes): {:?}", file_data),
    }
}

fn enter_password(socket: &UdpSocket) {
    print!("Enter the password: ");
    io::stdout().flush().unwrap();

    let mut password = String::new();
    io::stdin().read_line(&mut password).unwrap();
    let password = password.trim();

    let mut request = vec![1]; // EnterPassword code
    request.extend(password.as_bytes());
    socket.send(&request).expect("Couldn't send data");

    let mut buf = [0; BUFFER_SIZE];
    let (amt, _src) = socket.recv_from(&mut buf).expect("Didn't receive data");

    let response_code = buf[0];
    match response_code {
        1 => println!("Password accepted"),
        2 => println!("Password rejected"),
        _ => println!("Unexpected response code: {}", response_code),
    }
}
