% Chris Forte
% 9-Sep-2022
% Grayscale

% Read Color Image
pic = imread('coral_reef.jpg');
figure();
imshow(pic);

% Convert Color Image to Grayscale
gray = (0.2989 * double(pic(:, :, 1)) + 0.5870 * double(pic(:, :, 2)) + 0.1140 * double(pic(:, :, 3))) / 255;

% Show Grayscale Image
figure();
imshow(gray);
