function [] = question2()
%{
jskyzero 2017/10/09

Digital Image Processing
%}

lena_img = imread('LENA.png');
eight_am_img = imread('EightAM.png');



function map_table = get_map_table(img_matrix)
    [img_x, img_y] = size(img_matrix);
    img_length =  img_x * img_y;
    img_hist = imhist(img_matrix);
    sum_hist = @(x) sum(img_hist(1:x, :));
    cal_prob = @(x) x / img_length;
    img_cdf =  arrayfun(cal_prob, arrayfun(sum_hist, 1:256));
    change_table = img_cdf * 255;
    cal_table = @(x) uint8(round(x));
    map_table =  arrayfun(cal_table, change_table);
end

lena_map_table = get_map_table(lena_img);
eight_am_table = get_map_table(eight_am_img);

function neareast_index = get_neareast_index(value)
    neareast_index = 1;
    max_length = 255;
    function [] = checkone(index)
        if (lena_map_table(index) - value) <= max_length
            max_length = lena_map_table(index) - value;
            neareast_index = index;
        end  
    end
    arrayfun(@checkone, 1:256);
    neareast_index = uint8(neareast_index);
end

final_map_table = arrayfun(@get_neareast_index, eight_am_table);
map_value = @(x) final_map_table(x+1);
[x, y] = size(eight_am_img);
length =  x * y;
new_eight_am_img =  reshape(arrayfun(map_value, reshape(eight_am_img, [length, 1])), [x, y]);


hold on;
subplot(3,2,1);
imshow(eight_am_img);
xlabel('initial');
subplot(3,2,2);
imshow(new_eight_am_img);
xlabel('new');

subplot(3,2,3);
imhist(lena_img);
xlabel('lena_hist');
subplot(3,2,4);
imhist(eight_am_img);
xlabel('eight_am_hist');
subplot(3,2,5);
imhist(new_eight_am_img);
xlabel('new_eight_am_hist');

end