function [filter_img] = Blurring_Filter(img, a, b, T)
%{
jskyzero 2017/12/26

Digital Image Processing
%}

img = im2double(img);
[m, n] = size(img);

u = abs((1:m) - (m + 1) / 2);
v = abs((1:n) - (n + 1) / 2);

[V,U] = meshgrid(v,u);
D = U.*a+V.*b;

[V,U] = meshgrid((1:n), (1:m));
I = (-1).^(U + V);

blur_func = @(x) (T / (pi * x)) * sin(pi * x) * exp(-1i * pi * x);

H = arrayfun(blur_func, D);

filter_img = Filter(img.*I, H).*I;

end