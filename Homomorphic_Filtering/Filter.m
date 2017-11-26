function [ filter_img ] = Filter( initial_img, H)
%FILTER Summary of this function goes here
%   Detailed explanation goes here

F = fft2(initial_img);

F = F.*H;

filter_img = real(ifft2(F));

end

