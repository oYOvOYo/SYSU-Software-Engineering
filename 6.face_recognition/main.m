% main scripts of PCA face recognition 
% set test image file folder
file_path = './img';
% set repeat times
times = 1;

results = 0:times:1;

for x = 1:times:1
  result = face_recognition(file_path);
  results(x) = result;
  fprintf('%f\n', result);
end

fprintf('Means: %f Max: %f Min: %f\n', mean(results), max(results), min(results));