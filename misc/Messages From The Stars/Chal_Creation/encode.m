z = imread("unencoded.png");

% print the image to the screen
figure(1);			
imagesc(z);

% Normalize the pixel data in the loaded matrix to be between 0 and 1
z(z==255) = 0;
z(z==13) = 1;

Fs = 8192; 
Ts = 1/Fs;   
T = 0:Ts:(Fs*Ts)/20;  % 1/20th of a second 
T_pause = 0:Ts:(Fs*Ts)/20;  % 1/20th of a second 
Frq = 1000;  % Tone Frequency range
tone_one = cos(2*pi*(Frq+100)*T);  
tone_zero = cos(2*pi*(Frq-100)*T); 
Y0 = zeros(1, length(T_pause)); % Silent Interval

message = [];

for i = 1:size(z,1)
    for j = 1:size(z,2)
        if z(i,j,3) == 1
            message = [message tone_one];
        else
            message = [message tone_zero];
        end
        message = [message Y0];
    end
end

audiowrite("message_from_space.wav",message,Fs); % Save sound to file
