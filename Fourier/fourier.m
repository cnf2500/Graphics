%
% Author: Chris Forte
% Date: September 27, 2022
% Title: Fourier Transform
% Description: Produces a visual representation of an image's Fast Fourier Transform magnitude. 
 
% Read Color Photo
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
