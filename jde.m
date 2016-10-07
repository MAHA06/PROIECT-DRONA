fabric=imread('13.jpg');
lab = rgb2lab(fabric);
nColors = 2;
imwrite(fabric(:,:,1),'D:\PROIECT DRONA\TESTE_IMAGINE\red.bmp');
imwrite(fabric(:,:,2),'D:\PROIECT DRONA\TESTE_IMAGINE\green.bmp');
imwrite(fabric(:,:,3),'D:\PROIECT DRONA\TESTE_IMAGINE\blue.bmp');
d=size(lab(:,:,1));
t=lab(:,:,1);

% file=fopen('D:\PROIECT DRONA\TESTE_IMAGINE\imaj2.txt','w+');
% for i=1:d(1)
%     for j=1:d(2)
%         fprintf(file,'%f ',t(i,j));
%     end
%     fprintf(file,'\n');
% end
r=mat2gray(t);
imshow(r);
%imshow(t,[0 80]);
imwrite(lab(:,:,2),'D:\PROIECT DRONA\TESTE_IMAGINE\a.bmp');
imwrite(lab(:,:,3),'D:\PROIECT DRONA\TESTE_IMAGINE\b.bmp');
    

