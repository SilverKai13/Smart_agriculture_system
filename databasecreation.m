clc;
clear all;
close all;
%% MFCC Feature for Backward
aa = dir('database\Citrus Cancer\*.jpg');
for ij=1:length(aa)
    % Define variables
   i2 = 1:length(aa)
    aa1 = aa(i2).name;
    im = imread(fullfile('database\',aa1));
    im = imresize(im,[256,256]);
figure,imshow(im);title('Input image');
[r c d] = size(im);
if d == 3
    gray = im2double(rgb2gray(im));
else
    gray = im2double(im);
end
figure,imshow(gray);
% % 
points11 = detectSURFFeatures(gray);
figure,
imshow(im);
hold on; 
plot(selectStrongest(points11,100))
 % Extract the features.
[f1,vpts1] = extractFeatures(gray,points11);
f2 = mean(f1);
feature = [feature;f2];
end
save('feature','feature') 
