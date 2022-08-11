%avmaze2 after list format change to numeric columns

% close all, clear all

f1=figure;
% f2=figure;
% f3=figure;
% f4=figure;
% f5=figure;

animal='mouse2';
dates={'20220807on'};%{'20220617_1';'20220617_2';'20220619';'20220620';'20220621_1';'20220621_2';'20220622';'20220622_2';'20220622_3';'20220705_2'};%
events=[];
for file=1:numel(dates)
    date=dates{file, 1};
    filename=['C:\Data\av_maze\behavior_tracking_JunAug2022\' animal '_' date '.txt'];
    % Import csv
    opts = delimitedTextImportOptions("NumVariables", 9);
    opts.DataLines = [1, Inf];
    opts.Delimiter = "\t";
    opts.VariableNames = ["VarName1", "VarName2", "VarName3", "SessionBegins", "VarName5", "VarName6", "VarName7", "VarName8", "VarName9"];
    opts.VariableTypes = ["datetime", "datetime", "double", "categorical", "double", "double", "double", "double", "double"];
    opts = setvaropts(opts, 1, "InputFormat", "dd/MM/yyyy");
    opts = setvaropts(opts, 2, "InputFormat", "HH:mm:ss");
    opts = setvaropts(opts, 4, "EmptyFieldRule", "auto");
    opts.ExtraColumnsRule = "ignore";
    opts.EmptyLineRule = "read";
    events = [events; readtable(filename, opts)]; 
    % events(find(events.Type=={'end session'}),:)%read out list of events
    % opts.VariableTypes = ["string", "categorical", "double", "categorical", "categorical", "categorical"];
    % events = readtable(filename, opts);
    clear opts 
end

%% chop
% chop_from=datetime('2022-Jun-1 10:00:00.000','InputFormat','yyyy-MM-dd HH:mm:ss.SSS');
% chop_to=datetime('2022-Jun-13 21:00:00.000','InputFormat','yyyy-MM-dd HH:mm:ss.SSS');
bin=hours(1);

% x=datetime(events.(1),'InputFormat','yyyy-MM-dd HH:mm:ss.SSS');
% events(find(x<chop_from),:)=[];
% x=datetime(events.(1),'InputFormat','yyyy-MM-dd HH:mm:ss.SSS');
% events(find(x>chop_to),:)=[];
% x=datetime(events.(1),'InputFormat','yyyy-MM-dd HH:mm:ss.SSS');
% events(find(isnat(x)==1),:)=[];
% x(find(isnat(x)==1))=[];

x=events.(2);
event_type=events.(4);
cond=events.(6);
%% cleanup
%clean duplicates
clean_rows=[];
for row=2:size(events,1)
   if event_type(row)==event_type(row-1)
       clean_rows=[clean_rows row];
   end
end
events(clean_rows,:)=[];
x=events.(2);
event_type=events.(4);
cond=events.(6);

%clean spurious entry detections when animal has not gone to middle
%inbetween
w_all=find(event_type=='WATER TIME'); 
e_all=find(event_type=='end trial'); 
clean_rows=[];
for i=1:length(w_all)-1
    w=w_all(i); %current index
    e=e_all(find(e_all>w,1)); %next end
    if w_all(i+1)<e
        clean_rows=[clean_rows w_all(i+1)];
    end
end
events(clean_rows,:)=[];
x=events.(2);
event_type=events.(4);
cond=events.(6);

%% plot
y=ones(size(x))*3.5;

for i=1:size(event_type,1)
    str=char(event_type(i));
    pat1='New trial';
    pat2='MIDDLE BEAM BREAK';
    if isempty(strfind(str,pat1))==0 | isempty(strfind(str,pat2))==0
        y(i)=3.5;
    end
    pat1='nest';
    pat2='Nest';
    if isempty(strfind(str,pat1))==0 | isempty(strfind(str,pat2))==0
        y(i)=2;
    end   
    pat1='pellet';
    if isempty(strfind(str,pat1))==0
        y(i)=4;
    end
    pat1='water';
    if isempty(strfind(str,pat1))==0
        y(i)=3;
    end
end

y(find(event_type=='DINNER TIME'))=4; %food entry
y(find(event_type=='WATER TIME'))=3; %water entry
y(find(event_type=='SOCIAL TIME'))=5; %social entry
y(find(event_type=='Nest beam break'))=2; %nest entry
% y(find(event_type=='Food_retrieval'))=4;%pellet retrieval
y(find(event_type=='MIDDLE BEAM BREAK'))=3.5; %decision point logs

pel=NaN(size(x));
pel(find(event_type=='Pellet taken'))=4;
pel1=NaN(size(x));
pel1(find(event_type=='pellets delivered total1'))=4;
pel2=NaN(size(x));
pel2(find(event_type=='pellets delivered total2'))=4;
pel3=NaN(size(x));
pel3(find(event_type=='pellets delivered total3'))=4;
lick1=NaN(size(x));
lick1(find(event_type=='Total water drops delivered1'))=3;
lick2=NaN(size(x));
lick2(find(event_type=='Total water drops delivered2'))=3;
lick3=NaN(size(x));
lick3(find(event_type=='Total water drops delivered3'))=3;
lick4=NaN(size(x));
lick4(find(event_type=='Total water drops delivered4'))=3;


f2=figure; hold on;
h1 = histogram(cond(find(event_type=='pellets delivered total1'))-0.5);
h1.BinWidth = 0.5;
h2 = histogram(cond(find(event_type=='pellets delivered total2')),'FaceColor','k');
h2.BinWidth = 0.5;
h3 = histogram(cond(find(event_type=='pellets delivered total3'))+0.5,'FaceColor','r');
h3.BinWidth = 0.5;
h4 = histogram(cond(find(event_type=='DINNER TIME'))-1,'FaceColor','y');
h4.BinWidth = 0.5;
legend('1pel','2pel','3pel','food entry');
title('pellet condition codes');
ylabel('count');
unique(cond)
xticks([12 21 102 120 201 210]);
xticklabels({'012','021','102','120','201','210'});

f3=figure; hold on;
h1 = histogram(cond(find(event_type=='Total water drops delivered1'))-0.5);
h1.BinWidth = 0.5;
h2 = histogram(cond(find(event_type=='Total water drops delivered2')),'FaceColor','k');
h2.BinWidth = 0.5;
h3 = histogram(cond(find(event_type=='Total water drops delivered3'))+0.5,'FaceColor','r');
h3.BinWidth = 0.5;
h4 = histogram(cond(find(event_type=='Total water drops delivered4'))+1,'FaceColor','g');
h4.BinWidth = 0.5;
h5 = histogram(cond(find(event_type=='WATER TIME'))-1,'FaceColor','y');
h5.BinWidth = 0.5;
legend('1drop','2drop','3drop','4drop','water entry');
title('water condition codes');
ylabel('count');
xticks([12 21 102 120 201 210]);
xticklabels({'012','021','102','120','201','210'});

f4=figure; hold on;
h1 = histogram(cond(find(event_type=='DINNER TIME')));
h1.BinWidth = 0.5;
h2 = histogram(cond(find(event_type=='WATER TIME'))+0.5,'FaceColor','r');
h2.BinWidth = 0.5;
h3 = histogram(cond(find(event_type=='SOCIAL TIME'))+1,'FaceColor','g');
h3.BinWidth = 0.5;
legend('food entries','water entries','social entries');
title(' condition codes during entry');
ylabel('count');
xticks([12 21 102 120 201 210]);
xticklabels({'012','021','102','120','201','210'});

f5=figure;hold on;
F_low=size(find(cond(find(event_type=='Pellet taken'))==21 | cond(find(event_type=='Pellet taken'))==12),1);
F_med=size(find(cond(find(event_type=='Pellet taken'))==102 | cond(find(event_type=='Pellet taken'))==120),1);
F_high=size(find(cond(find(event_type=='Pellet taken'))==201 | cond(find(event_type=='Pellet taken'))==210),1);
plot([1 2 3],[F_low F_med F_high],'ko-')
W_low=size(find(cond(find(event_type=='Lick detected'))==102 | cond(find(event_type=='Lick detected'))==201),1);
W_med=size(find(cond(find(event_type=='Lick detected'))==12 | cond(find(event_type=='Lick detected'))==210),1);
W_high=size(find(cond(find(event_type=='Lick detected'))==21 | cond(find(event_type=='Lick detected'))==120),1);
plot([1 2 3],[W_low W_med W_high],'bo-')
%get soc durations from the prerecorded ms values
% soc_dur=events.(9);
% S_low=(sum(soc_dur(find(event_type=='social time end' & cond==120)))+sum(soc_dur(find(event_type=='social time end' & cond==210))))/1000;
% S_med=(sum(soc_dur(find(event_type=='social time end' & cond==201)))+sum(soc_dur(find(event_type=='social time end' & cond==21))))/1000
% S_high=(sum(soc_dur(find(event_type=='social time end' & cond==12)))+sum(soc_dur(find(event_type=='social time end' & cond==102))))/1000

%or calculate from timestamps
sl=[];sm=[];sh=[];
marks=find(event_type=='social time end');
for j=1:size(marks,1)
    i=marks(j);
    if cond(i)==120 | cond(i)==210
        sl=[sl seconds(x(i+1)-x(i-1))];%next one is mid beam this one is forced to zero
    elseif cond(i)==201 | cond(i)==21
        sm=[sm seconds(x(i+1)-x(i-1))];
    elseif cond(i)==12 | cond(i)==102
        sh=[sh seconds(x(i+1)-x(i-1))];
    end
end
S_low=(sum(sl));
S_med=(sum(sm));
S_high=(sum(sh));

plot([1 2 3],[S_low S_med S_high],'go-')
legend('food','water','social');
title('consumed/condition');
ylabel('pels/lickDets/seconds');
xlabel('availability');
xticks([1 2 3]);
xticklabels({'low','medium','high'});

f6=figure;hold on;
F_low=size(find(cond(find(event_type=='DINNER TIME'))==21 | cond(find(event_type=='DINNER TIME'))==12),1);
F_med=size(find(cond(find(event_type=='DINNER TIME'))==102 | cond(find(event_type=='DINNER TIME'))==120),1);
F_high=size(find(cond(find(event_type=='DINNER TIME'))==201 | cond(find(event_type=='DINNER TIME'))==210),1);
plot([1 2 3],[F_low F_med F_high],'ko-')
W_low=size(find(cond(find(event_type=='WATER TIME'))==102 | cond(find(event_type=='WATER TIME'))==201),1);
W_med=size(find(cond(find(event_type=='WATER TIME'))==12 | cond(find(event_type=='WATER TIME'))==210),1);
W_high=size(find(cond(find(event_type=='WATER TIME'))==21 | cond(find(event_type=='WATER TIME'))==120),1);
plot([1 2 3],[W_low W_med W_high],'bo-')
S_low=size(find(cond(find(event_type=='SOCIAL TIME'))==120 | cond(find(event_type=='SOCIAL TIME'))==210),1);
S_med=size(find(cond(find(event_type=='SOCIAL TIME'))==201 | cond(find(event_type=='SOCIAL TIME'))==21),1);
S_high=size(find(cond(find(event_type=='SOCIAL TIME'))==12 | cond(find(event_type=='SOCIAL TIME'))==102),1);
plot([1 2 3],[S_low S_med S_high],'go-')
legend('food','water','social');
title('entries/condition');
ylabel('entries');
xlabel('availability');
xticks([1 2 3]);
xticklabels({'low','medium','high'});

%binarized consumption of pellets
f7=figure;hold on;

F_low=size(find(cond(find(event_type=='pellets delivered total1' | event_type=='pellets delivered total2' | event_type=='pellets delivered total3'))==21 | cond(find(event_type=='pellets delivered total1' | event_type=='pellets delivered total2' | event_type=='pellets delivered total3'))==12),1);
F_med=size(find(cond(find(event_type=='pellets delivered total1' | event_type=='pellets delivered total2' | event_type=='pellets delivered total3'))==102 | cond(find(event_type=='pellets delivered total1' | event_type=='pellets delivered total2' | event_type=='pellets delivered total3'))==120),1);
F_high=size(find(cond(find(event_type=='pellets delivered total1' | event_type=='pellets delivered total2' | event_type=='pellets delivered total3'))==201 | cond(find(event_type=='pellets delivered total1' | event_type=='pellets delivered total2' | event_type=='pellets delivered total3'))==210),1);
plot([1 2 3],[F_low F_med F_high],'ko-')
W_low=size(find(cond(find(event_type=='Total water drops delivered1' | event_type=='Total water drops delivered2' | event_type=='Total water drops delivered3'))==102 | cond(find(event_type=='Total water drops delivered1' | event_type=='Total water drops delivered2' | event_type=='Total water drops delivered3'))==201),1);
W_med=size(find(cond(find(event_type=='Total water drops delivered1' | event_type=='Total water drops delivered2' | event_type=='Total water drops delivered3'))==12 | cond(find(event_type=='Total water drops delivered1' | event_type=='Total water drops delivered2' | event_type=='Total water drops delivered3'))==210),1);
W_high=size(find(cond(find(event_type=='Total water drops delivered1' | event_type=='Total water drops delivered2' | event_type=='Total water drops delivered3'))==21 | cond(find(event_type=='Total water drops delivered1' | event_type=='Total water drops delivered2' | event_type=='Total water drops delivered3'))==120),1);
plot([1 2 3],[W_low W_med W_high],'bo-')
S_low=size(find(cond(find(event_type=='SOCIAL TIME'))==120 | cond(find(event_type=='SOCIAL TIME'))==210),1);
S_med=size(find(cond(find(event_type=='SOCIAL TIME'))==201 | cond(find(event_type=='SOCIAL TIME'))==21),1);
S_high=size(find(cond(find(event_type=='SOCIAL TIME'))==12 | cond(find(event_type=='SOCIAL TIME'))==102),1);
plot([1 2 3],[S_low S_med S_high],'go-')
legend('food consum entries','water consum entries','social');
title('entries/condition');
ylabel('entries');
xlabel('availability');
xticks([1 2 3]);
xticklabels({'low','medium','high'});



% room_door_open=find(event_type=='room door opened');
% room_door_close=find(event_type=='room door closed');
starts=find(event_type=='Session Begins');
% ends=find(event_type=='END');

% %refine ends
% ends(find(ends<starts(1)))=[]; %clean ends before first start
% for i=1:size(starts,1)-1
%     next_start=starts(i+1);
%     next_end=ends(find(ends>starts(i),1));
%     if next_start<next_end
%         refined_ends(i)=next_start-1;
%     else
%         refined_ends(i)=next_end;
%     end
% end
% if ends(end)>starts(end)
%     refined_ends(end+1)=ends(end);
% else
%     starts(end)=[];
% end
% clear ends
% ends=refined_ends';

% session_starts=find(event_type=='begin session');
% session_ends=find(event_type=='end session');
% y([starts; ends])=2;
yy=fillmissing(y,'linear');

figure(f1); hold on;
plot(x,yy,'k');hold on
plot(x,y,'ko');hold on
plot(x,pel1,'y*','MarkerSize',5,'LineWidth',2);
plot(x,pel2,'y*','MarkerSize',10,'LineWidth',3);
plot(x,pel3,'y*','MarkerSize',12,'LineWidth',5);

plot(x,lick1,'c*','MarkerSize',5,'LineWidth',2);
plot(x,lick2,'c*','MarkerSize',10,'LineWidth',3);
plot(x,lick3,'b*','MarkerSize',12,'LineWidth',4);
plot(x,lick4,'b*','MarkerSize',15,'LineWidth',7);
plot(x,cond/100,'r');
plot(x,[diff(cond); 0],'b');
title(animal);
yticks([2 3 3.5 4 5]);
plot([x(1) x(end)],[3.5 3.5],'k--');
yticklabels({'nest','water','decision point','food','social'});
ylabel('area');
ylim([0 5.5]);
xlim([x(1) x(end)]);


% for i=1:length(starts)
%     plot([x(starts(i)) x(starts(i))],[1 5],'g');
% end
% for i=1:length(ends)
%     plot([x(ends(i)) x(ends(i))],[1 5],'r');
% end
% for i=1:1:length(first_lick)
%     subplot(size(animals,1),1,a),plot([x(first_lick(i)) x(first_lick(i))],[2.4 2.8],'c');
% end

% h(1)=plot(x(end),1,'y*','MarkerSize',10,'LineWidth',3);
% legend(h,'eat 14mg pellet','Location','South');