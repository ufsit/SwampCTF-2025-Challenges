[message, Fs] = audioread("../to_upload/message_from_space.wav");

segment_size = 410; % number of samples of each tone, or 1/10th of a second at 8192 Htz
num_segments = length(message)/segment_size; % break up the message into the different segments each 1/10th of a second long

section_start = 1;
section_end = segment_size; % Set the first audio segment to encompass the first tone bit

binary_output = [];

% Loop over all of the tones while skipping the quite sections of the audio
% file
for i = 1:num_segments/2

    % At SwampCTF we love the Fourier transform <3
    % This command takes segments of the signal, in this case every tone,
    % and decomposes the tone into it's frequencies. In this case the
    % command takes a bunch of frequency categories and computes how close
    % it is to each one.
    [s, f] = stft(message(section_start:section_end), Fs);
    
    if abs(s(f == 1088)) > 30 % Check to see if the frequency is close to the 1100 Htz range, if it is write a zero to the binary array
        binary_output = [binary_output 0];
    elseif abs(s(f == 896)) > 30 % Check to see if the frequency is close to the 900 Htz range, if it is write a one to the binary array
        binary_output = [binary_output 1];
    else
        % If the threshold is not met for either freq don't do anything and
        % print some debug info
        fprintf("STFT ISSUE: %d\n 896: %f\n 1088: %f\n", i, abs(s(f == 896)), abs(s(f == 1088)))
    end

    % increment the segment frame to be over the next tone
    section_start = section_start + segment_size*2;
    section_end = section_end + segment_size*2;
end

% Reformat the array into a square matrix, the message is 6 241 bytes long,
% this is important because it is a semi prime number with roots 79*79.
matrix2D = reshape(binary_output, [sqrt(length(binary_output)), sqrt(length(binary_output))]);

% Plot the matrix showing ones as white squares and zeros as black squares
imshow(matrix2D', []);