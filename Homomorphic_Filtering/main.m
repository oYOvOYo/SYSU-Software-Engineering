barb_img = imread('barb.png');


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

%{
figure
subplot(3,2,1);
imshow(ans);
xlabel('initial');
%}
