%% 
function [Irms,P] = RMScurrent_Power_ForwardTPCMode220241226(phi,D,M)
%RMSCURRENT_FORWARD 此处显示有关此函数的摘要
%   此处显示详细说明
    I_point=[];
    t=[];
    P=0;
    varphi=phi;
    % 根据 phi 和 D 计算电流点（I_point）和时间（t）
    if varphi>=0 && varphi<abs(0.5-D)
        I_point=[M - 2*D - 4*M*varphi, M - 2*D, 4*M*varphi - M - 2*D + 4*D*M, 2*D - M + 4*M*varphi, 2*D - M, 2*D + M - 4*M*varphi - 4*D*M, M - 2*D - 4*M*varphi];
        t=[0,             varphi,     0.5-D,          0.5,           0.5+varphi,     1-D,  1];
        P=-D*(2*D + 4*varphi - 1);
    elseif varphi >=abs(0.5-D) && varphi<0.5
        I_point= [M - 2*D - 4*M*varphi, 3*M - 2*D - 4*M*varphi - 4*D*M, 2*D + M + 4*varphi - 2, 2*D - M + 4*M*varphi, 2*D - 3*M + 4*M*varphi + 4*D*M, 2 - M - 4*varphi - 2*D, M - 2*D - 4*M*varphi];
        t=[0,         0.5-D,         varphi,          0.5,           1-D,     0.5+varphi,1];
        P=2*D^2 + 4*D*varphi - 3*D + 4*varphi^2 - 4*varphi + 1;

    elseif varphi>=0.5 && varphi<abs(0.5-D)+0.5
        I_point=[4*M*varphi - 3*M - 2*D, -2*D - M, 3*M - 2*D - 4*M*varphi - 4*D*M, 2*D + 3*M - 4*M*varphi, 2*D + M, 2*D - 3*M + 4*M*varphi + 4*D*M, 4*M*varphi - 3*M - 2*D];
        t=[0,         varphi-0.5,            0.5-D,          0.5,               varphi,     1-D,1];
        P=D*(2*D + 4*varphi - 3);
    elseif varphi>=abs(0.5-D)+0.5 && varphi<1
        I_point=[- 3*M + 4*M*varphi - 2*D, 4*M*varphi - 5*M - 2*D + 4*D*M, 2*D - M + 4*varphi - 4, 2*D + 3*M - 4*M*varphi, 2*D + 5*M - 4*M*varphi - 4*D*M, M - 2*D - 4*varphi + 4, - 3*M + 4*M*varphi - 2*D];
        t=[0,         0.5-D,     varphi-0.5,          0.5,       1-D,             varphi,1];
        P = -2*D^2 - 4*D*phi + 5*D - 4*phi^2 + 8*phi - 4;
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

