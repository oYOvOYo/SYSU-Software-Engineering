%{
jskyzero 2017/12/26

Digital Image Processing
%}

book_img = imread('book_cover.jpg');

hold on;
subplot(3,3,1);
imshow(book_img, []);
xlabel('Initial');

subplot(3,3,2);
blur_img = Blurring_Filter(book_img, 0.1, 0.1, 1);
imshow(blur_img, []);
xlabel('Blurring Filter');

subplot(3,3,3);
noise_img = Gaussian_Noise(blur_img, 0, 500);
imshow(noise_img, []);
xlabel('Gaussian Noise');


subplot(3,3,4);
inverse_img = Inverse_Filter(blur_img, 0.1, 0.1, 1);
imshow(inverse_img, []);
xlabel('Inverse Filter');

subplot(3,3,5);
inverse_noise_img = Inverse_Filter_With_Noise(noise_img, 0.1, 0.1, 1);
imshow(inverse_noise_img, []);
xlabel('Inverse Filter With Noise');

K_list = [0.01, 0.1, 1];
for i = 1:3
  K = K_list(i);
  subplot(3, 3, 6+i);
  wiener_img = Wiener_Filter(noise_img, 0.1, 0.1, 1, 0.01);
  imshow(wiener_img, []);
  xlabel(sprintf('Wiener Filter With k = %f', K));
end



