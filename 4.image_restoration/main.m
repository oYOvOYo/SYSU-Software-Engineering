book_img = imread('book_cover.jpg');

hold on;
subplot(3,2,1);
imshow(book_img);
xlabel('Initial');

subplot(3,2,2);
blur_img = Blurring_Filter(book_img, 0.1, 0.1, 1);
imshow(blur_img);
xlabel('Blurring Filter');

subplot(3,2,3);
noise_img = Gaussian_Noise(blur_img, 0, 500);
imshow(noise_img);
xlabel('Gaussian Noise');