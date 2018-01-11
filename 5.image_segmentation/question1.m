function [] = question1()
%QUESTION1 
%   Dilation / Erosion / Opening / Closing

% initial set 8x7 image
initial_img = [0 0 0 0 0 0 0;
               0 0 1 1 0 0 0;
               0 0 0 1 0 0 0;
               0 0 0 1 1 0 0;
               0 0 1 1 1 1 0;
               0 0 1 1 1 0 0;
               0 1 0 1 0 1 0;
               0 0 0 0 0 0 0];

 
 function[result] = process(img, mask, center, type)
   [img_row, img_col] = size(img);
   [mask_row, mask_col] = size(mask);
   center_row = center(1);
   center_col = center(2);
   % padding
   if center_row > 1
     img = padarray(img, [center_row - 1,0], 'pre');
   end
   if center_col > 1
     img = padarray(img, [0, center_col - 1], 'pre');
   end
   if mask_row - center_row > 0
     img = padarray(img, [mask_row - center_row, 0], 'post');
   end
   if mask_col - center_col > 0
     img = padarray(img, [0, mask_col - center_col], 'post');
   end
   %  image to column
   img = im2col(img, [mask_row, mask_col]);
   mask = reshape(mask, [mask_row * mask_col, 1]);
   
   % Dilation
   % dilation = @(a, b) (a * transpose(b)) >= min(sum(b), 1);
   % Reosion
   % reosion = @(a, b) (a * transpose(b)) == sum(b);
   
   % cal result
   if strcmp(type, 'dilation')
     result = sum(bsxfun(@eq, img, mask)) >= min(sum(mask), 1);
   end
   if strcmp(type, 'reosion')
     result = sum(bsxfun(@eq, img, mask)) == sum(mask);
   end
   
   result =  reshape(double(result), [img_row, img_col]);
 end


a = process(initial_img, [1, 1, 1], [1, 1], 'dilation');
b = process(initial_img, [1, 1, 1], [1, 1], 'reosion');
c = process(initial_img, [1 1; 0 1], [1, 2], 'dilation');
d = process(initial_img, [1 1; 0 1], [1, 2], 'reosion');
% open R D
e1 = process(b, [1, 1, 1], [1, 1], 'dilation');
% close D R
f1 = process(a, [1, 1, 1], [1, 1], 'reosion');

e2 = process(d, [1 1; 0 1], [1, 2], 'dilation');
f2 = process(c, [1 1; 0 1], [1, 2], 'reosion');

end

