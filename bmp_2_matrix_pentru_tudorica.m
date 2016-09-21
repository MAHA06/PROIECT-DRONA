A=imread('D:\PROIECT DRONA\HARTA\2','bmp');

muie=fopen('D:\imaj2.txt','w+');

d = size(A);
b=zeros(d(1),d(2));
c=zeros(d(1),d(2));
d(1)
d(2)
 fprintf(muie,'%d %d\n',d(1),d(2));
for i=1:d(1)
    for j=1:d(2)
        
        r = A(i,j,1);
        g = A(i,j,2);
        b = A(i,j,3);
        if((r<30) && (g<30) && (b<30))
            b(i,j)=255;
            
        elseif(r+10> g+b)
            b(i,j)=50;
        elseif(b+10>g+r)
            b(i,j)=100;
        else
            b(i,j)=0;
        end;
           
           fprintf(muie,'%d ',b(i,j));
            
           if(b(i,j)<10)
             fprintf(muie,'  ');
           elseif(b(i,j)<100)
               fprintf(muie,' '); 
           end;
     
         
      
        
    end;
     fprintf(muie,'\n'); 
end;



   
   

  
 



 
