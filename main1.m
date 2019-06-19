% % % % % Leaf Detection
clc;
clear all;
close all;
warning('off','all');
% [filename,pathname] = uigetfile('*.jpg');
% % im = imread([pathname,filename]);
% im = imresize(im,[256 256]);
% % figure
% % imshow(im);
% % % % % Feature Extraction
aa = dir('database\*.jpg');
feature = [];
for i2 = 1:length(aa)
    aa1 = aa(i2).name;
    im = imread(fullfile('database\',aa1));
    im = imresize(im,[256,256]);
figure,imshow(im);title('Input image');
% % % % % database creation
cam = webcam('USB2.0 PC CAMERA'); 
preview(cam);
for i=1
    pause(5);
    a = snapshot(cam);
im = imresize(a,[256 256]);
imwrite(im,'data\18.jpg');
end
figure,imshow(im),title('resized image')
end
[r c d] = size(im);
if d == 3
    gray = im2double(rgb2gray(im));
else
    gray = im2double(im);
end
% figure,imshow(gray);
% % 
points11 = detectSURFFeatures(gray);
figure,
imshow(im);
hold on; 
plot(selectStrongest(points11,100))
 % Extract the features.
[f1,vpts1] = extractFeatures(gray,points11);
f2 = mean(f1);
% feature = [feature;f2];
% end
% save('feature','feature')  
load feature.mat;
% % classification
lab = [1,3,3,3,4,4,4,4,1,1,1,2,2,2,2,3];
mdl = fitcknn(feature,lab);
yfit = predict(mdl,f2);
% % Decision Making
if yfit == 1
    ccf = 1;
    msgbox('Citrus Cancer');
    disp('Citrus Cancer');
 elseif yfit == 2
    ccf = 2;
    msgbox('Citrus Greening Disease');   
    disp('Citrus Greening Disease');
     elseif yfit == 3
    ccf = 3;
    msgbox('Citrus Whitefly');
    disp('Citrus Whitefly');
     elseif yfit == 4
    ccf = 4;
    msgbox('Scooty Mold');
    disp('Scooty Mold');
   end
% Hardware implementation
instrumentObjects=instrfind;  % don't pass it anything - find all of them.
delete(instrumentObjects)
a=serial('COM5','BaudRate',9600);
fopen(a);
    if ccf == 1
       fprintf(a, '%c', 'A');
    elseif ccf == 2
          fprintf(a, '%c', 'B');
            elseif ccf == 3
          fprintf(a, '%c', 'C');
            elseif ccf == 4
          fprintf(a, '%c', 'D');
%             elseif ccf == 5
%           fprintf(a, '%c', '5');
    end
fclose(a);