% Chris Forte
% 16-Oct-2022
% Mandelbrot Image

% Program to Produce Mandelbrot Image
function mandelbrot(n, niter)

x1 = -2; x2 = 1;
y1 = -1.5; y2 = 1.5;

[x,y] = meshgrid(linspace(x1, x2, n), linspace(y1, y2, n));

% Stores the Trajectory of Each Point
a = x + 1i * y;
b = zeros(size(a));
c = zeros(size(a));

% Finds the Value of Each Trajectory 
for ii = 1:niter
    b = b.^2 + a;
    c(abs(b) > 2 & c == 0) = niter - ii;
end

% Plots Image Trajectories
figure,
imagesc(c),
colormap hot
axis square

end

