% Chris Forte
% Sep-27-2022
% Fourier Transform
 
% Read color photo
image = imread('coral_reef.jpg');
figure();
imshow(image);
title("Color Image");
 
% Convert to Grayscale
gray = rgb2gray(image);

figure();
imshow(gray);
title("Grayscale Image");

% Calculate the Fast Fourier Transform
F = fft2(double(gray));
S = fftshift(F);
L = log2(S);
A = abs(L);
figure();
imagesc(A);
axis image;
title("Magnitude of FFT Image");
