function [filter_img] = Butterworth_Filter(img, D0, rank)
%{
jskyzero 2017/12/26

Digital Image Processing
%}

img = im2double(img);
[m, n] = size(img);

u = abs((1:m) - (m + 1) / 2);
v = abs((1:n) - (n + 1) / 2);

[V,U] = meshgrid(v,u);
D = sqrt(U.^2+V.^2);

[V,U] = meshgrid((1:n), (1:m));
I = (-1).^(U + V);


H = 1./((D./D0 + 1).^rank);

filter_img = Filter(img.*I, H).*I;

end