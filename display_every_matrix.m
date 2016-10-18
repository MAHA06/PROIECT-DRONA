function varargout = display_every_matrix(varargin)
% DISPLAY_EVERY_MATRIX MATLAB code for display_every_matrix.fig
%      DISPLAY_EVERY_MATRIX, by itself, creates a new DISPLAY_EVERY_MATRIX or raises the existing
%      singleton*.
%
%      H = DISPLAY_EVERY_MATRIX returns the handle to a new DISPLAY_EVERY_MATRIX or the handle to
%      the existing singleton*.
%
%      DISPLAY_EVERY_MATRIX('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in DISPLAY_EVERY_MATRIX.M with the given input arguments.
%
%      DISPLAY_EVERY_MATRIX('Property','Value',...) creates a new DISPLAY_EVERY_MATRIX or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before display_every_matrix_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to display_every_matrix_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help display_every_matrix

% Last Modified by GUIDE v2.5 18-Oct-2016 22:41:51

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @display_every_matrix_OpeningFcn, ...
                   'gui_OutputFcn',  @display_every_matrix_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before display_every_matrix is made visible.
function display_every_matrix_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to display_every_matrix (see VARARGIN)

% Choose default command line output for display_every_matrix
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes display_every_matrix wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = display_every_matrix_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;



function edit1_Callback(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit1 as text
%        str2double(get(hObject,'String')) returns contents of edit1 as a double


% --- Executes during object creation, after setting all properties.
function edit1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
str=get(handles.edit1, 'string');
file=fopen(str);
mat= dlmread(str);
d=size(mat);

for i=1 : d(1)
    for j=1 : d(2)
        mat(i,j)=128-mat(i,j);
       
    end
end
a=mat2gray(mat);

%1958 1669
fclose(file);
imshow(a);
