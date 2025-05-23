%% 
function [Irms,P] = RMScurrent_Power_ForwardTPCMode2(phi,D,M0)
%RMSCURRENT_FORWARD 此处显示有关此函数的摘要
%   此处显示详细说明
    I_point=[];
    t=[];
    P=0;
    varphi=phi;
    % 根据 phi 和 D 计算电流点（I_point）和时间（t）
    if varphi>=0 && varphi<abs(0.5-D)
        I_point=[
            M0 + 2*abs((D - 0.5)) - 4*M0*varphi - 1,... 
            M0 + 2*abs((D - 0.5)) - 1,...
            M0 + 2*abs((D - 0.5)) + 4*M0*varphi - 4*M0*abs((D - (1/2))) - 1,...
            4*M0*varphi - 2*abs((D - (1/2))) - M0 + 1,... 
            1 - 2*abs((D - 0.5)) - M0,...
            4*M0*abs((D - 0.5)) - 2*abs((D - 0.5)) - 4*M0*varphi - M0 + 1,...
            M0 + 2*abs((D - 0.5)) - 4*M0*varphi - 1];
        t=[0,             varphi,     abs(0.5-D),          0.5,           0.5+varphi,     0.5+abs(0.5-D),  1];
        %P=(2*varphi - abs((D - 0.5)))*(2*abs((D - 0.5)) - 1);
    elseif varphi >=abs(0.5-D) && varphi<0.5
        I_point=[M0 + 2*abs((D - 0.5)) - 4*M0*varphi - 1,...
            M0 + 2*abs((D - 0.5)) - 4*M0*varphi + 4*M0*abs((D - (1/2))) - 1,...
            M0 + 4*varphi - 2*abs((D - 0.5)) - 1,...
            4*M0*varphi - 2*abs((D - 0.5)) - M0 + 1,...
            4*M0*varphi - 2*abs((D - 0.5)) - M0 - 4*M0*abs((D - (1/2))) + 1,... 
            2*abs((D - 0.5)) - 4*varphi - M0 + 1,...
            M0 + 2*abs((D - 0.5)) - 4*M0*varphi - 1];
        t=[0,         abs(0.5-D),         varphi,          0.5,           0.5+abs(0.5-D),     0.5+varphi,1];
        %P=4*varphi^2 - 4*varphi*abs((D - 0.5)) - 2*varphi + 2*abs((D - 0.5))^2 + abs((D - 0.5));

    elseif varphi>=0.5 && varphi<abs(0.5-D)+0.5
        I_point=[2*abs((D - 0.5)) - 3*M0 + 4*M0*varphi - 1,...
            2*abs((D - (1/2))) - M0 - 1,...
            M0 + 2*abs((D - 0.5)) - 4*M0*varphi + 4*M0*abs((D - 0.5)) - 1,...
            3*M0 - 2*abs((D - 0.5)) - 4*M0*varphi + 1,...
            M0 - 2*abs((D - 0.5)) + 1,...
            4*M0*varphi - 2*abs((D - 0.5)) - M0 - 4*M0*abs((D - 0.5)) + 1,...
            2*abs((D - 0.5)) - 3*M0 + 4*M0*varphi - 1];
        t=[0,         varphi-0.5,            abs(0.5-D),          0.5,               varphi,     0.5+abs(0.5-D),1];
        %P=(2*abs((D - (1/2))) - 1)*(abs((D - (1/2))) - 2*varphi + 1);
    elseif varphi>=abs(0.5-D)+0.5 && varphi<1
        I_point=[2*varphi - 3*M0 + 4*M0*varphi - 2,...
            2*varphi - 3*M0 + 4*M0*varphi - 4*M0*abs((D - (1/2))) - 2,...
            2*varphi - M0 - 2,...
            3*M0 - 2*varphi - 4*M0*varphi + 2,...
            3*M0 - 2*varphi - 4*M0*varphi + 4*M0*abs((D - (1/2))) + 2,...
            M0 - 2*varphi + 2,...
            2*varphi - 3*M0 + 4*M0*varphi - 2];
        t=[0,         abs(0.5-D),     varphi-0.5,          0.5,       0.5+abs(0.5-D),             varphi,1];
        %P=- 2*varphi^2 + 3*varphi - 1;
    end
    % 使用插值拟合
    [t_uni,index1,index2]=unique(t,'stable');%本函数主要画出irms与D和phi的关系曲线，为什么要取出非重复值并只保留原始序列的时刻及其电流值。答；除去重复值
    

    fitModel = fit(t_uni', transpose(I_point(index1)), 'linearinterp');
    t_fit = linspace(min(t), max(t), 200);
    I_fit = feval(fitModel, t_fit);%将参数代入函数
    %plot(t_fit,I_fit)
    
    % 计算 Irms
    Irms=rms(I_fit(2:end));
end

