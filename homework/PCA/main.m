% Principal Component Analysis
% jskyzero 2018/06/10

% run in octave
% import for normc
% pkg load miscellaneous

%  set global variables
FILE_NAME = "yale_face.mat";

%
% main part
%

% load data
data = load(FILE_NAME);
data = data.X;
[M, N] = size(data);
IMAGE_SIZE = [sqrt(M), sqrt(M)];
TEST_IMAGE = data(:, 1);

% means
means = transpose(mean(transpose(data)));
% covariance matrix
X = bsxfun(@minus, data, means);
X = X * transpose(X) ;

% compute eigenvectors
tic;
% use svd
[U, Sigma, ~] = svd(X);
time_svd = toc;
% use eig
[V, D] = eig(X);
time_eig = toc - time_svd;
% more process
V = X * V;
V = normc(V);


% PCA
U_10 = U(:, 1:10);
U_100 = U(:, 1:100);
TEST_10 = pinv(U_10) * TEST_IMAGE;
TEST_100 = pinv(U_100) * TEST_IMAGE;

cal_variance = @(x, y) sum((x - y).^2);
TEST_variance = cal_variance(TEST_IMAGE, means);
TEST_10_variance_percentage = cal_variance(U_10 * TEST_10, means) / TEST_variance;
TEST_100_variance_percentage = cal_variance(U_100 * TEST_100, means) / TEST_variance;

hold on;
subplot(3,5,1);
imshow(reshape(TEST_IMAGE, IMAGE_SIZE), []);
xlabel('1st image');

subplot(3,5,2);
imshow(reshape(means, IMAGE_SIZE), []);
xlabel('mean image');

subplot(3,5,3);
imshow(reshape(U_10 * TEST_10, IMAGE_SIZE), []);
xlabel('U10 image');

subplot(3,5,4);
imshow(reshape(U_100 * TEST_100, IMAGE_SIZE), []);
xlabel('U100 image');


for i = 1:1:5
  subplot(3,5,5 + i);
  imshow(reshape(U(:, i), IMAGE_SIZE), []);
  xlabel(sprintf('svd %d eigenvector', i));
end

for i = 1:1:5
  subplot(3,5,10 + i);
  imshow(reshape(V(:, i), IMAGE_SIZE), []);
  xlabel(sprintf('eig %d eigenvector', i));
end