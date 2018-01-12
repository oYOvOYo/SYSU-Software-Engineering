function [ train_datas, test_datas ] = datas_split( datas )
%DATA_SPLIT datas
%   train_dats, test_datas

train_percentage = 0.7;

[img_size, people_size, each_people_img_size] = size(datas);

each_people_train_size = floor(each_people_img_size * train_percentage);
train_datas = zeros(img_size, people_size, each_people_train_size);
test_datas = zeros(img_size, people_size, each_people_img_size - each_people_train_size);

% read each imgs
for people_index = 1:1:people_size
  train_index = randperm(each_people_img_size, each_people_train_size);
  test_index = setdiff(1:1:each_people_img_size, train_index);

  train_datas(:,people_index,:) = datas(:,people_index,(train_index));
  test_datas(:,people_index,:) = datas(:,people_index,(test_index));
end

end

