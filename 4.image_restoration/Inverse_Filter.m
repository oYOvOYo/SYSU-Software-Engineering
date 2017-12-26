function [filter_img] = Inverse_Filter(img, a, b, T)
%{
jskyzero 2017/12/26

Digital Image Processing
%}

img = im2double(img);
[m, n] = size(img);

u = (1:m) - m / 2 - 1;
v = (1:n) - n / 2 - 1;

[V,U] = meshgrid(v,u);
D = U.*a+V.*b;


blur_func = @(x) (T / (pi * x)) * sin(pi * x) * exp(-1i * pi * x);
H = arrayfun(blur_func, D);
H(D==0) = T;

[V,U] = meshgrid((1:n), (1:m));
I = (-1).^(U + V);


F = fft2(img.*I);
% sample inverse
F = F./H;
% must after fft so can't use common filter
F(abs(H) < 0.001) = 0;

filter_img = (real(ifft2(F))).*I;

end

