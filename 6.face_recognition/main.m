% main scripts of PCA face recognition 
% set test image file folder
file_path = './img';

% set repeat times
times = 10;
k_size = 6;

results = 1:1:times;

for k = 1:1:k_size
  for x = 1:1:times 
    result = face_recognition(file_path, 2^k);
    results(x) = result;
    % fprintf('%f\n', result);
  end
  fprintf('k=%f Means: %f Max: %f Min: %f\n',2^k, mean(results), max(results), min(results));
end

