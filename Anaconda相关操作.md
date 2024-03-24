# Anaconda相关操作

## 一、管理环境

 在Anaconda Prompt上

  ###    1.创建新环境

 `  conda create -n env_name packages_names`

- `env_name`即创建的环境名，建议以英文命名且不加空格，

- `packages_names`及安装在环境中的包名。

  （1）如果要安装指定的版本号，则只需要在包名后面以=和版本号的形式执行。如：conda create –n python3 python=3.8。即创建一个名为“python3”的环境，环境中安装版本为3.8的python。

  （2）如果要在新创建的环境中创建多个包，则直接在 package_names 后以空格隔开，添加多个包名即可。如：conda create -n python3 python=3.5 numpy pandas。即创建一个名为“python3”的环境，环境中安装版本为3.5的python，同时也安装了numpy和pandas。

  -n为-name。
### 2.切换环境

  `activate env-name`
  (1)env_name 换成创建的环境名。如果创建环境后安装Python时没有指定Python的版本，那么将会安装与Anaconda版本相同的Python版本，即如果安装Anaconda第3版，则会自动安装Python 3.x。

  当成功切换环境之后，在该行行首将以“(env_name)”或“[env_name]”开头。其中，“env_name”为切换到的环境名。

  ### 3.退出环境至root
  `deactivate`
  (1)当执行退出当前环境，回到root环境命令后，原本行首以“(env_name)”或“[env_name]”开头的字符将不再显示。

  ### 4.显示已创建环境
  `conda info -e`

  或`conda env list`

  结果中星号“*”所在行即为当前所在环境，默认创建的环境名为“base”。

  ### 5.复制环境
  `conda create -n new_env_name -clone copied_env_name`

  copied_env_name 即为被复制/克隆环境名。

  new_env_name 即为复制之后新环境的名称。

  如：conda create –n py38 –clone python38，即为克隆名为“python38”的环境，克隆后的新环境名为“py38”。此时，环境中将同时存在“python38”和“py38”环境，且两个环境的配置相同。

  ### 6.删除环境
  `conda remove -n env_name --all`

  `env_name` 为被删除环境的名称。

  ## 二、管理包

  ### 1.查找可供安装的包版本
  #### (1)精确查找

  `conda search --full-name package_name`

  -full-name 为精确查找的参数。

  package_full_name 是被查找包的全名。

  例如：`conda search –full-name python`即查找全名为“python”的包有哪些版本可供安装。

  #### (2）模糊查找

  `conda search text`

  text 是查找含有此字段的包名。

  例如：`conda search py` 即查找含有“py”字段的包，有哪些版本可供安装。

  ### 2.获取当前环境中已安装的包信息

  `conda list`
  执行上述命令后将在终端显示当前环境已安装包的包名及其版本号。

  ### 3.安装包
  #### (1）在指定环境中安装包

  `conda install -n env_name package_name`

  `env_name` 即将包安装的指定环境名。

  `package_name `即要安装的包名。

  例如：`conda install –name python38 pandas`即在名为“python38”的环境中安装pandas包。

  #### (2）在当前环境中安装包

  `conda install package_name`

  `package_name` 即要安装的包名。

  执行命令后在当前环境中安装包。

  例如：`conda install pandas` 即在当前环境中安装pandas包。

  #### (3）使用pip安装包

  当使用`conda install`无法进行安装时，可以使用pip进行安装。例如：see包。

  `pip install package_name`

  `package_name `为指定安装包的名称。

  如：`pip install see `即安装see包。

  pip只是包管理器，无法对环境进行管理。因此如果想在指定环境中使用pip进行安装包，则需要先切换到指定环境中，再使用pip命令安装包。

  pip无法更新python，因为pip并不将python视为包。

  pip可以安装一些conda无法安装的包；conda也可以安装一些pip无法安装的包。因此当使用一种命令无法安装包时，可以尝试用另一种命令。

  #### (4）从http://Anaconda.org安装包

  【使用场景】

  当使用conda install无法进行安装时，可以考虑从 http://Anaconda.org 中获取安装包的命令，并进行安装。

  【注意】
  从 http://Anaconda.org 安装包时，无需注册。

  在当前环境中安装来自于http://Anaconda.org的包时，需要通过输入要安装的包在http://Anaconda.org中的路径作为获取途径（channel）。查询路径的方式如下：

  在浏览器中输入：http://anaconda.org，或直接点击http://Anaconda.org

  在新页面“Anaconda Cloud”的上方搜索框中输入要安装的包名，然后回车，就出现搜索结果了。


  搜索结果中有数以千计的包可供选择，此时点击“Downloads”可根据下载量进行排序，最上面的为下载最多的包。（图中以搜索bottleneck包为例）

  选择满足需求的包或下载量最多的包，点击包名。

  复制“ To install this package with conda run one of the following: ”下方的命令，并粘贴在命令行终端中执行。

  完成安装。

  ### 4.卸载包
  #### (1）卸载指定环境中的包

  `conda remove -n env_name package_name`

  `env_name `即卸载包所在指定环境的名称。

  `package_name` 即要卸载包的名称。

  例如：`conda remove –name python2 pandas`即卸载名为“python2”中的pandas包。

  #### (2）卸载当前环境中的包

  `conda remove package_name`

  `package_name` 即要卸载包的名称。

  执行命令后即在当前环境中卸载指定包。

  例如：`conda remove pandas `即在当前环境中卸载pandas包。

  ### 5.更新包
  #### (1）更新所有包

  `conda update --all`
  或`conda upgrade --all`

  建议： 在安装Anaconda之后执行上述命令更新Anaconda中的所有包至最新版本，便于使用。

  #### (2）更新指定包

  `conda update package_name`

  或`conda upgrade package_name`

  `package_name` 为指定更新的包名。

  更新多个指定包，则包名以空格隔开，向后排列。如：`conda update pandas numpy matplotlib`即更新pandas、numpy、matplotlib包。

  ### 三、Anaconda常用命令表
  功能说明	命令
  查看conda版本	`conda --version / conda -V`
  更新conda	`conda update conda`
  查看conda帮助	`conda --help / conda -h`
  切换conda环境	`conda activate env_name`
  新建虚拟环境	`conda create --n env_name package_names`
  退出虚拟环境	`conda deactivate`
  列出所有虚拟环境	`conda info --envs / conda info -e / conda env list`
  复制环境	`conda create --n new_env_name --clone copied_env_name`
  删除环境	`conda remove --n env_name --all`
  精确查找包	`conda search --full-n package_name`
  模糊查找包	`conda search`
  获取当前环境中已安装的包信息	`conda list`
  指定环境安装包	`conda install --n env_name package_names`
  指定版本	`conda install --n env_name package_name=version`
  在当前环境中安装包	`conda install package_names`
  pip安装	`pip install package_names` conda装不了的或没有的，可用pip来安装

  

  

  