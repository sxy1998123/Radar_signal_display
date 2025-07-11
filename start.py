import sys
import subprocess
import os
import signal
import time

def resource_path(relative_path):
    """ 获取资源的绝对路径。用于PyInstaller打包后访问资源 """
    try:
        # PyInstaller创建的临时文件夹，存储路径在 _MEIPASS
        base_path = sys._MEIPASS
    except AttributeError:
        base_path = os.path.abspath(".")
    
    return os.path.join(base_path, relative_path)

def start_process(executable_path):
    """ 启动进程并处理路径中的空格 """
    print('启动路径:', executable_path)
    
    # 处理路径中的空格（Windows需要特殊处理）
    if sys.platform == 'win32':
        # 使用原始字符串避免转义问题
        executable_path = f'"{executable_path}"'
        return subprocess.Popen(executable_path, shell=True)
    else:
        return subprocess.Popen([executable_path])

if __name__ == "__main__":
    try:
        # 获取资源路径（兼容打包和未打包环境）
        frontend_path = resource_path(os.path.join('frontend', 'RadarSignalDisplay.exe'))
        backend_path = resource_path(os.path.join('app', 'app.exe'))
        
        print(f"前端路径: {frontend_path}")
        print(f"后端路径: {backend_path}")
        
        # 检查文件是否存在
        if not os.path.exists(frontend_path):
            raise FileNotFoundError(f"前端应用不存在: {frontend_path}")
        if not os.path.exists(backend_path):
            raise FileNotFoundError(f"后端应用不存在: {backend_path}")
        
        # 启动后端应用
        backend_process = start_process(backend_path)
        print("后端应用已启动，等待初始化...")
        
        # 给后端一些启动时间
        time.sleep(3)
        
        # 启动前端应用
        frontend_process = start_process(frontend_path)
        print("前端应用已启动")
        
        # 等待前端进程结束
        frontend_process.wait()
        print("前端应用已关闭")
        
    except Exception as e:
        print(f"启动失败: {str(e)}")
        input("按Enter键退出...")  # 防止窗口立即关闭
    finally:
        # 确保后端进程被终止
        if 'backend_process' in locals():
            print("正在停止后端应用...")
            backend_process.terminate()
            try:
                backend_process.wait(timeout=5)
            except subprocess.TimeoutExpired:
                backend_process.kill()
        
        # 添加延迟确保进程完全退出
        time.sleep(1)