file=fopen('D:\out.txt');
a=fscanf(file,'%d',[656 375  ]);

b=mat2gray(a);




%imwrite(b,'D:\generatTarget.bmp');
imshow(transpose(b));


fclose(file);



