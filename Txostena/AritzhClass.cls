\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{AritzhClass}[2014/10/11 Aritzh's LaTeX clas]

\LoadClassWithOptions{article}

% Begin parsing options

\newif\ifaritzh@tbat
\newif\ifaritzh@sekziopuntu
\newif\ifaritzh@eusk

\DeclareOption{eusk}{\aritzh@eusktrue}
\DeclareOption{ezeusk}{\aritzh@euskfalse}

\DeclareOption{tbat}{\aritzh@tbattrue}
\DeclareOption{eztbat}{\aritzh@tbatfalse}

\DeclareOption{sekziopuntu}{\aritzh@sekziopuntutrue}
\DeclareOption{ezsekziopuntu}{\aritzh@sekziopuntufalse}

% Default options
\ds@eusk
\ds@tbat
\ds@sekziopuntu

\ProcessOptions\relax
% End parsing options

% Begin package dependencies
\RequirePackage{geometry}
\RequirePackage{calc}
\geometry{a4paper, margin=1.5cm, centering, includeheadfoot}

\RequirePackage{fancyhdr}
\RequirePackage{amsmath, amssymb, latexsym}
\RequirePackage{graphics, graphicx}
\RequirePackage[latin1]{inputenc}
\RequirePackage[load=prefixed]{siunitx}
\RequirePackage[siunitx]{circuitikz}
\RequirePackage{titling}
\RequirePackage{selinput}
\RequirePackage{amsthm}
\RequirePackage{thmtools}
\RequirePackage{listings}
\RequirePackage{epstopdf}
\RequirePackage{ifthen}
\RequirePackage{float}
\RequirePackage{tabularx}

\ifaritzh@tbat
  \RequirePackage[T1]{fontenc}
\fi

\ifaritzh@eusk
	\RequirePackage[basque]{babel}
\fi

\ifaritzh@sekziopuntu
	\renewcommand{\thesection}{\arabic{section}.}
	\renewcommand{\thesubsection}{\arabic{section}.\arabic{subsection}.}
	\renewcommand{\thesubsubsection}{\arabic{section}.\arabic{subsection}.\arabic{subsubsection}.}
\fi

% End package dependencies

\SelectInputMappings{%
  aacute={á},
  ntilde={ñ},
  Euro={€}
}


% Begin "listings" (algorithms) configuration
\makeatletter
\newcommand{\ProcessDigit}[1]
{%
  \ifnum\lst@mode=\lst@Pmode\relax%
   {\color{orange!75!black} #1}%
  \else
    #1%
  \fi
}

\lstset{%
	backgroundcolor=\color{white},
	basicstyle=\footnotesize\ttfamily,
	commentstyle=\itshape\color{white!50!black},
	keywordstyle=\bfseries\color{blue},
	stringstyle=\color{blue!50!red},
	identifierstyle=\color{orange!20!black},
	numbers=left,
	numbersep=5pt,
	numberstyle=\tiny\color{white!50!black},
	xleftmargin=1.5cm,
	tabsize=4,
	literate=
    {0}{{{\ProcessDigit{0}}}}1
    {1}{{{\ProcessDigit{1}}}}1
    {2}{{{\ProcessDigit{2}}}}1
    {3}{{{\ProcessDigit{3}}}}1
    {4}{{{\ProcessDigit{4}}}}1
    {5}{{{\ProcessDigit{5}}}}1
    {6}{{{\ProcessDigit{6}}}}1
    {7}{{{\ProcessDigit{7}}}}1
    {8}{{{\ProcessDigit{8}}}}1
    {9}{{{\ProcessDigit{9}}}}1,
}

\lstdefinelanguage{algoritmoa}{%
	morekeywords={hasiera, algoritmo, baldin, orduan, bestela, ambaldin, amaia, bitartean, ambitartean, egin, edo, eta, guztietarako, tik, etik, raino, rainoko, alderantziz, funtzio, itzuli, konstantea, bektorea},
	sensitive=false,
	morecomment=[l]{--},
	morecomment=[s][\color{black!50!white}]{<}{>}
}

\lstdefinelanguage[Custom]{Ada}[2005]{Ada}{morecomment=[s][\color{black!50!white}]{<}{>}}

% Begin title configuration
\newcommand{\izenburua}[1]{\renewcommand{\@izenburua}{#1} \title{#1}}
\newcommand{\@izenburua}{Aldatu \textbackslash izenburua erabiliz}

\newcommand{\data}[1]{\renewcommand{\@data}{#1}}
\newcommand{\@data}{\today}

\newcommand{\azpiizenburua}[1]{\renewcommand{\@azpiizenburua}{#1}}
\newcommand{\@azpiizenburua}{}

\date{%
\@data an \vspace{0.5cm} \\
}

\newcommand{\eginizenburua}[1][true]{%
	\ifthenelse{\equal{#1}{true}}{\vspace*{1.5cm}}{}
	\begin{center}
		\huge \bfseries \scshape \@izenburua \normalfont
		\par
		\ifthenelse{\equal{\@azpiizenburua}{}}{\par\vskip 0.5em}{\bfseries \scshape \Large \@azpiizenburua \normalfont \par\vskip 0.5em}
		\Large - \theauthor\, - \par\vskip 0.5em
		\@date
		\small Euskal Herriko Unibertsitatea - Universidad del País Vasco \\
		\small Informatika Ingeniaritzako Gradua - Grado en Ingeniería Informática
	\end{center}
}

\newcommand{\izenburuorrialdea}{\null\vfill\thispagestyle{empty}\eginizenburua[false]\vfill\pagebreak}
% End title configuration

% Begin fancyhdr configuration
\newcommand\smalltitle[1]{\renewcommand\@smalltitle{#1}}
\newcommand\@smalltitle{Aldatu \textbackslash smalltitle erabiliz}

\newcommand\ikasgaia[1]{\renewcommand\@ikasgaia{#1}}
\newcommand\@ikasgaia{Aldatu \textbackslash ikasgaia erabiliz}

\newcommand{\tableofcontentsnotitle}{\@starttoc{toc}}
\newcommand{\orrialdetxuria}{\pagebreak\null\thispagestyle{empty}\pagebreak}

\pagestyle{fancy}
\fancyhead{}
\fancyhead[LO]{\theauthor}						% Left odd (and even) head
\fancyhead[RO]{\bfseries \@smalltitle}			% Right odd (and even) head
\fancyfoot{}
\fancyfoot[LO]{\@ikasgaia}		% Left odd (and even) foot
\fancyfoot[CO]{\bfseries \thepage .orrialdea}	% Center odd (and even) foot
\fancyfoot[RO]{EHU/UPV}							% Right odd (and even) foot
\renewcommand{\headrulewidth}{0.4pt}
\renewcommand{\footrulewidth}{0.4pt}
% End fancyhdr configuration

% Begin adding shorter commands for common tasks
\newcommand{\NN}{\mathbb{N}}
\newcommand{\PP}{\mathbb{P}}
\newcommand{\ZZ}{\mathbb{Z}}
\newcommand{\II}{\mathbb{I}}
\newcommand{\QQ}{\mathbb{Q}}
\newcommand{\RR}{\mathbb{R}}
\newcommand{\CC}{\mathbb{C}}

\newcommand{\osag}[1]{#1^\complement}
\newcommand{\ez}[1]{\overline{#1}}

\newcommand{\nonbat}{\,\:%
\begin{tikzpicture}[scale=2]%
	\draw[transform canvas={yshift=-0.3em}, semithick] (0, 0) -- (0.3ex, 1.4ex);
\end{tikzpicture}\,\:}

\newcommand{\nonbi}{\,\:%
\begin{tikzpicture}[scale=2]%
	\draw[transform canvas={yshift=-0.5em}, semithick] (0, 0) -- (0.5ex, 2ex);
\end{tikzpicture}\,\:}

\newlength\savedwidth
\newcommand\whline[1]{%
  \noalign{%
    \global\savedwidth\arrayrulewidth\global\arrayrulewidth 1pt%
  }%
  \cline{#1}%
%  \noalign{\vskip\arrayrulewidth}%
  \noalign{\global\arrayrulewidth\savedwidth}%
}

\newcommand{\xor}{\oplus}
\newcommand{\barne}[1]{\stackrel{\circ}{#1}}

\newcommand{\orrierref}[1]{\pageref{#1}. orrialdea}
\newcommand{\bhline}{\noalign{\global\arrayrulewidth1pt} \hline \noalign{\global\arrayrulewidth0.4pt}  \hline}
\newcommand{\bvline}{\vrule width 1pt}
\newcommand{\spcl}[2][c]{\begin{tabular}[#1]{@{}c@{}}#2\end{tabular}}

\newcommand{\sartuada}[1]{%
	\begin{minipage}{\linewidth}
		\lstinputlisting[language=Ada, breaklines=true]{#1}
	\end{minipage}
}

\newcommand{\sartualgoritmoa}[1]{
	\begin{minipage}{\linewidth}
		\lstinputlisting[language=algoritmoa, breaklines=true]{#1}
	\end{minipage}
}

\newcommand{\nirearray}[3]{
	\begin{array}{#1}
		#2 \\
		#3
	\end{array}
}

\newcommand{\csection}[2][]{%
	\section*{#2}
	\ifx&#1&
		\addcontentsline{toc}{section}{#2}
	\else
		\addcontentsline{toc}{section}{#1}	
	\fi
	\addtocounter{section}{1}
	\setcounter{subsection}{0}
	\setcounter{subsubsection}{0}
}

\newcommand{\oharpar}[2]{\begin{tabularx}{\textwidth}{lX}
#1 & #2
\end{tabularx}}

\newcommand{\bito}{\leftrightarrow}
% End adding shorter commands for common tasks

% Begin useful environments for tables
\newenvironment{taula}[3]{%
   \begin{table}[ht]
   \ifx&#1&
   \else
      \caption{#1}
   \fi
   \label{#2}
   \begin{center}
   \begin{tabular}{#3}
}{%
   \end{tabular}
   \end{center}
   \end{table}
}

\newenvironment{ltaula}[3]{%
   \begin{table}[H]
   \ifx&#1&
   \else
      \caption{#1}
   \fi
   \label{#2}
   \begin{tabular}{#3}
}{%
   \end{tabular}
   \end{table}
}

\newcommand{\bitaula}[8]{%
	\begin{table}[!htb]
		\begin{minipage}{.5\linewidth}
			\ifx&#1&
			\else
				\caption{#1}
			\fi
			\label{#2}
			\begin{center}
				\begin{tabular}{#3}
					#4
				\end{tabular}
			\end{center}
		\end{minipage}%
		\ifx&#8&
		\else
			\begin{minipage}{.5\linewidth}
				\ifx&#1&
				\else
					\caption{#5}
				\fi
				\label{#6}
				\begin{center}
					\begin{tabular}{#7}
						#8
					\end{tabular}
				\end{center}
			\end{minipage}%
		\fi
	\end{table}
}
% End useful environments for tables

% Begin shorthand environments for code

\newenvironment{ada}{\begin{lstlisting}[language=Ada]}{\end{lstlisting}}

\newenvironment{algoritmoa}{\begin{lstlisting}[language=algoritmoa]}{\end{lstlisting}}

% End shorthand environments for code
