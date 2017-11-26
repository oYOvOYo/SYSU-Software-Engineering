function [filter_img] = Homomorphic_Filtering(img, D0)
%{
jskyzero 2017/12/26

Digital Image Processing
%}

yH = 2.0;
yL = 0.25;
C = 1;

img = im2double(img);
[m, n] = size(img);

u = abs((1:m) - (m + 1) / 2);
v = abs((1:n) - (n + 1) / 2);

[V,U] = meshgrid(v,u);
D = sqrt(U.^2+V.^2);

[V,U] = meshgrid((1:n), (1:m));
I = (-1).^(U + V);


H =  1 - exp((-(D.^2)/(D0^2)).*C);
H = (yH - yL) * H + yL;


filter_img = exp(Filter(log(img).*I, H).*I);


min_value = min(min(filter_img));
max_value = max(max(filter_img));
range = max_value - min_value;
filter_img = (filter_img - min_value) / range;

end
