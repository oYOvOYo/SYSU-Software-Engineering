function [ result ] = face_recognition( img_path, k )
%FACE_RECOGNITION img_path
%   percentage


datas = read_images(img_path);
[train_datas, test_datas] = datas_split(datas);

[img_size, people_size, each_people_train_size] = size(train_datas);
[~, ~, each_people_test_size] = size(test_datas);
train_size = people_size *  each_people_train_size;
test_size = people_size * each_people_test_size;

B = train_datas(:,:,1);

train_matrix = reshape(train_datas, [img_size, train_size]);
train_matrix_mean = transpose(mean(transpose(train_matrix)));
X = bsxfun(@minus, train_matrix, train_matrix_mean);
[V, D] = eig(transpose(X) * X);
% I = V*transpose(V);

V = V(:, (train_size - k + 1:1:train_size));
V = X * V;
V = normc(V);

model_datas = zeros(k, train_size);
for case_index = 1:1:train_size
  each_img = train_matrix(:,case_index);
  model_datas(:,case_index) = pinv(V) * (each_img - train_matrix_mean);
end

success = 0;


% read each test imgs
for people_index = 1:1:people_size
  for img_index = 1:1:each_people_test_size
    each_img = test_datas(:,people_index, img_index);
    each_img = pinv(V) * (each_img - train_matrix_mean);
    compare_matrix = bsxfun(@minus, model_datas, each_img);
    compare_matrix = compare_matrix.^2;
    compare_result = sum(compare_matrix);
    
    min_reault = min(compare_result);
    min_index = find(min_reault == compare_result);
    find_result = mod((min_index - 1 ), people_size) + 1;
    
    if find_result == people_index
      success = success + 1;
    end
  end
end

result = success / test_size;
end

