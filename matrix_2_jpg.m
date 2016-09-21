
A=imread('D:\PROIECT DRONA\prima2','bmp');
fileID = fopen('D:\PROIECT DRONA\matrix2.txt','w+');

d = size(A);
 fprintf(fileID,'%d %d\n',d(1),d(2));
for i=1:d(1)
    for j=1:d(2)
        str1 = A(i,j,1);
        str2 = A(i,j,2);
        str3 = A(i,j,3);
        if(str1==str2&&str2==str3)
            if(str1==0)
                
            fprintf(fileID,'%d ',255);
            elseif (str1==255)
                fprintf(fileID,'%d ',0);
            end;
        else
            if(str1==255)
                fprintf(fileID,'%d ',50);
            else if (str2==255)
                    if(str3==255)
                        
                    
                       fprintf(fileID,'%d ',200);
                    else
                        fprintf(fileID,'%d ',150);
                    end;  
                    else  
                    
                fprintf(fileID,'%d ',100);
            end;
        end;
       
        
        
    end;
    end;
   
    fprintf(fileID,'\n');
    
    
    
end;
fclose(fileID);
 

A=imread('D:\PROIECT DRONA\trei_trei','bmp');
fileID = fopen('D:\PROIECT DRONA\matrix3.txt','w+');

d = size(A);
 fprintf(fileID,'%d %d\n',d(1),d(2));
for i=1:d(1)
    for j=1:d(2)
        str1 = A(i,j,1);
        str2 = A(i,j,2);
        str3 = A(i,j,3);
        if(str1==str2&&str2==str3)
            if(str1==0)
                
            fprintf(fileID,'%d ',255);
            elseif (str1==255)
                fprintf(fileID,'%d ',0);
            end;
        else
            if(str1==255)
                fprintf(fileID,'%d ',50);
            else if (str2==255)
                    if(str3==255)
                        
                    
                       fprintf(fileID,'%d ',200);
                    else
                        fprintf(fileID,'%d ',150);
                    end;  
                    else  
                    
                fprintf(fileID,'%d ',100);
            end;
        end;
       
        
        
    end;
    end;
   
    fprintf(fileID,'\n');
    
    
    
end;
fclose(fileID);
 

 


