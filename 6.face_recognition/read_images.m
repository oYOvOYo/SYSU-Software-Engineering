function [ datas ] = read_images( img_path )
%READ_IMAGES img_path
%   (rows*cols:people_nums:each_people_imgs)

% set const value
img_raws = 112;
img_cols = 92;
people_size = 40;
each_people_img_size = 10;

% initial datas
datas = zeros(img_raws, img_cols, people_size, each_people_img_size);

% read each imgs
for people_index = 1:1:people_size
  for img_index = 1:1:each_people_img_size
    % strcat img_path
    each_img_path = strcat(img_path, '/s', num2str(people_index), '/', num2str(img_index), '.pgm');
    % read img from img_path and store to datas
    each_img = imread(each_img_path);
    datas(:,:,people_index,img_index) = each_img;
  end
end

% make [m, n] matrix to [m * n, 1] vector
datas = reshape(datas, [img_raws * img_cols, people_size, each_people_img_size]);

end
