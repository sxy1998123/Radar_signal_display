# 雷达信号生成及展示

前端 vue2，后端 flask python 3.11.11

## 前端开发启动

```sh
cd radar_signal_display_frontend
yarn install # 安装环境
yarn electron:serve # 启动
```

## 后端开发启动

先 conda 切换环境 python3.11.11

```sh
cd radar_signal_display_backend
pip install -r requirements.txt
flask run --port 5000
```

## 前端打包

```sh
cd radar_signal_display_frontend
yarn electron:build
```

## 后端打包

```sh
cd radar_signal_display_backend
pyinstaller -F app.py
```

## 合并

将前端打包后的 win-unpacked 文件夹和后端生成的 app.exe 文件放在一起，同时开启即可，若需要一键启动可以将 start.py 放到前后端两个目录外面，然后 pyinstaller --add-data "frontend;frontend" --add-data "backend;backend" -F start.py，运行生成后的 start.exe 即可。