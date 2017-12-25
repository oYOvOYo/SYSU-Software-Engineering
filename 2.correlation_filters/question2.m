function [] = question1()
%{
jskyzero 2017/10/22

try to do median filter

%}

car_img = imread('sport car.pgm');
  function noise_img = addNoise(img)
    [x, y] = size(img);
    length = numel(img);
    img = reshape(img, [length,1]);
    
    img= im2double(img);
    t1 = rand(size(img));
    t2 = rand(size(img));
    while (sum(t1 == t2) > 0)
      t1 = rand(size(img));
      t2 = rand(size(img));
    end
    
    function new_value = eachNoise(index)
      if (img(index) > t1(index))
          new_value = 1;
      elseif (img(index) < t2(index))
          new_value = 0;
      else
          new_value = img(index);
      end
    end
%   uint8 version, will stuck in while loop
%    t1 = randi(255, [length,1], 'like', img);
%    t2 = randi(255, [length,1], 'like', img);
%    while (sum(t1 == t2) > 0)
%      t1 = randi(255, [length,1], 'like', img);
%      t2 = randi(255, [length,1], 'like', img);
%    end 

%    function new_value = eachNoise(index)
%      if (img(index) > t1(index))
%          new_value = uint8(255);
%      elseif (img(index) < t2(index))
%          new_value = uint8(0);
%      else
%          new_value = img(index);
%      end
%    end
    
    noise_img = arrayfun(@eachNoise, 1:length);
    noise_img = reshape(noise_img, [x, y]);
  end

noise_img = addNoise(car_img);

function output = myMedianFilter(img)
  source_img = im2double(img);
  [source_x, source_y] = size(source_img);
  mask_x = 3; mask_y = 3;
  source_pad = padarray(source_img, [floor(mask_x/2) floor(mask_y/2)]);
  source = im2col(source_pad, [mask_x mask_y], 'sliding');


  filter = median(bsxfun(@times, source, ones(mask_x * mask_y, 1)));
  output = col2im(filter, [mask_x mask_y], size(source_pad), 'sliding');
end

function new = looptimes(img, times)
  new = img;
  for index = 1:times
    new = myMedianFilter(new);
  end
end

function new = looptimes2(img, times)
  new = img;
  for index = 1:times
    new = medfilt2(new);
  end
end


hold on;

subplot(3,2,1);
imshow(car_img);
title('initial');

subplot(3,2,2);
imshow(noise_img);
title('add noise');

subplot(3,2,3);
imshow(myMedianFilter(noise_img));
title('Mine');

subplot(3,2,4);
imshow(medfilt2(noise_img));
title('sample');

subplot(3,2,5);
imshow(looptimes(noise_img, 10));
title('Mine 10 times after');

subplot(3,2,6);
imshow(looptimes2(noise_img, 10));
title('sample 10 times after');


end