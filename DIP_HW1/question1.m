%{
jskyzero 2017/10/09

Digital Image Processing
%}

river_img = imread('river.JPG');

% save img info 
[img_x, img_y] = size(river_img);
img_length =  img_x * img_y;
% 
river_hist = imhist(river_img);
sum_hist = @(x) sum(river_hist(1:x, :));
cal_prob = @(x) x / img_length;
river_cdf =  arrayfun(cal_prob, arrayfun(sum_hist, 1:256));
change_table = river_cdf * 255;

% to array

map_value = @(x) uint8(round(change_table(x+1)));
% new_river_img =  arrayfun(map_value, reshape(river_img, [img_length, 1]));
new_river_img =  reshape(arrayfun(map_value, reshape(river_img, [img_length, 1])), [img_x, img_y]);
sample_river_img = histeq(river_img);

hold on;
subplot(1,3,1);
imshow(river_img);
xlabel('initial');
subplot(1,3,2);
imshow(new_river_img);
xlabel('mine');
subplot(1,3,3);
imshow(sample_river_img);
xlabel('sample');