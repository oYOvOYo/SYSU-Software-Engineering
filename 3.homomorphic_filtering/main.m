barb_img = imread('barb.png');
office_img =  rgb2gray(imread('office.jpg'));


hold on;
subplot(3,2,1);
imshow(barb_img);
xlabel('initial');
subplot(3,2,2);
imshow(Butterworth_Filter(barb_img, 10, 1));
xlabel('10');
subplot(3,2,3);
imshow(Butterworth_Filter(barb_img, 20, 1));
xlabel('20');
subplot(3,2,4);
imshow(Butterworth_Filter(barb_img, 40, 1));
xlabel('40');
subplot(3,2,5);
imshow(Butterworth_Filter(barb_img, 80, 1));
xlabel('80');


figure
subplot(4,2,1);
imshow(office_img);
xlabel('initial');
subplot(4,2,2);
imshow(Butterworth_Filter(office_img, 80, 1));
xlabel('Butterworth Filter D0=10');
subplot(4,2,3);
imshow(Homomorphic_Filtering(office_img, 10));
xlabel('D0=10');
subplot(4,2,4);
imshow(Homomorphic_Filtering(office_img, 100));
xlabel('D0=100');
subplot(4,2,5);
imshow(Homomorphic_Filtering(office_img, 1000));
xlabel('D0=1000');
subplot(4,2,6);
imshow(Homomorphic_Filtering(office_img, 10000));
xlabel('D0=10000');
subplot(4,2,7);
imshow(Homomorphic_Filtering(office_img, 2000));
xlabel('D0=2000');
subplot(4,2,8);
imshow(Homomorphic_Filtering(office_img, 4000));
xlabel('D0=4000');
