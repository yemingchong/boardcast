# boardcast
轻量的c++消息驱动框架 ， 只依赖c++11

目标是把服务器里面各个逻辑模块隔离开来，让服务器代码实现高内聚低耦合。

-observer 
  观察者类 用于管理注册的侦听对象和分发消息
  
-facade
  外观类 全局访问的唯一接口
  
-ilistener
  侦听接口类，所有的逻辑模块都拥有这个类的接口，做为模块唯一的对外接口类。

\documentclass[a4paper,12pt]{article}
\usepackage[utf8]{inputenc}
\usepackage{CJKutf8}
\usepackage{makeidx}
\usepackage{glossaries}
\usepackage[unicode]{hyperref}
\usepackage{todonotes}
\usepackage{marginnote}
\usepackage{booktabs}
\usepackage{color, soulutf8}
\usepackage{siunitx} %自动逗号分割数字
\usepackage{smartdiagram}
\usepackage{newfloat}
\usepackage{listings}
\usepackage{tcolorbox}
%\usepackage{minted} 程序员代码语法高亮
\usepackage{fancyvrb} %程序员代码语法高亮
\usepackage{algorithmicx} %算法库
\usepackage{tikz} %绘图库
\usetikzlibrary{matrix,calc,shapes}
\usepackage{dirtree}

\begin{document}
	
	\begin{CJK*}{UTF8}{gkai}
		
		\title{流剑服务器配置生成工具文档}
		\author{Huang Tao}
		%\textcopyright
		\maketitle
		\thispagestyle{empty} %不要页码
		\clearpage

	\section{安装部署}\label{sec:install}
	\paragraph{1.}
	创建一张Mysql表，用于存储配置信息 \newline
	sql \newline
	\clearpage
	\section{相关命令}\label{sec:command}
	\paragraph{}
	\begin{table}[!h]
		\begin{tabular}{l|c}
			\hline
			命令 & 注解 \\ 
			\hline
			-f[id] & 查找命令 \\
			\hline
			-i[id,address,server...] & 插入命令\\
			\hline
			-g[id] & 生成命令\\
			\hline
			--id & 填充大区ID\\
			\hline
			--address & 填充地址\\
			\hline
		\end{tabular}
	\end{table} 
	\paragraph{example}
	样例
	\newline
	查看1区部署情况\hspace{.1cm} -f 1
	\newline
	插入服务器信息,加一个lobby\hspace{.1cm} -i --id 1 --address 127.0.0.1 --lobby 1
	\newline
	生成1区的配置\hspace{.1cm} -g 1
	\newline
	默认生成一套新的配置\hspace{.1cm} -i --id 1 --address 127.0.0.1 --gate 1 --login 1 --room 1 --lobby 1 --db 1 --redis\_trans 1 --redis\_cache 1 --coordinator 1 --social 1 --community 1 --log 1 --maintain 1 --bill 1 --replay 1 --download 1 --rtserver 1 --rtservice 1 --dlserver 1 --idip 1
	
	\paragraph{}
	
	\clearpage
	\section{注意事项}\label{sec:notice}
	\paragraph{}
	各个服务器的起始结束ID,各个配置表的模板参数.
	
	\clearpage
	\section{结构示意}\label{sec:structs}
	\paragraph{1.}
	文件目录结构
	\dirtree{%
		.1 /.
		.2 172.18.160.81.
		.3 gate1.
		.3 gate2.
		.3 room1.
		.4 room\_server\_config.xml.
		.4 server\_config.xml.
		.3 game\_server\_config.xml.
		.3 gate\_server\_config.xml.
		.3 maintain\_server\_config.xml.
		.3 room\_server\_config.xml.
		.3 server\_config.xml.
		.2 172.18.160.82.
	}
	\paragraph{1.1}
	注解 \newline
	在\textbf{172.18.160.81}目录下的配置文件是各个server不多开的默认配置文件，如果有多开的server会在这个目录下生成如\textbf{gate1,gate2,room1}等,如果是此类多开的服务器则使用该目录下的配置，比如第2个roomserver 应该使用room1 目录下的配置+roomserver.exe 执行\newline
	这里要特别注意下\textbf{lobby} 如果多开lobbyserver lobbyserver的配置需要从lobby0, lobby1...中分别拿取 不能使用根目录下的server\_config.xml

	
	\clearpage
	\paragraph{2.}
	数据在Mysql中的内部结构
	\dirtree{%
		.1 /.
		.2 1.
		.3 172.18.160.82.
		.4 login1.
		.5 id 90001.
		.5 inner 8001.
		.5 out 9001.
		.4 login2.
		.4 maintain.
		.5 id 10001.
		.5 inner 8501.
		.3 172.18.160.81.
		.4 gate1.
		.4 gate2.
		.4 room1.
		.4 room2.
		.3 172.18.160.82.
		.4 lobby.
		.4 commnuity.
		.4 social.
		.2 2.
	}
	\paragraph{2.1}
	注解
	\newline
	\textbf{1} 大区ID \textbf{172.18.160.82} 各个物理机的IP地址 \textbf{login1} 物理机下面的servers
	\textbf{id} server的ID \textbf{inner} server的内部端口号 \textbf{out} server对外的端口号


	\end{CJK*}	
	
\end{document}
