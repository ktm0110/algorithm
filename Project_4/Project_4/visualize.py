import sys
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import glob

def load_obstacles(filename="map.txt"):
    try:
        with open(filename, 'r') as f:
            num_obstacles = int(f.readline())
            obstacles = [list(map(int, f.readline().split())) for _ in range(num_obstacles)]
        return obstacles
    except FileNotFoundError:
        print(f"파일 찾을 수 없음")
        return None

def load_path(filename):
    try:
        path_x, path_y = [], []
        with open(filename, 'r') as f:
            for line in f:
                parts = list(map(float, line.split()))
                path_x.append(parts[0])
                path_y.append(parts[1])
        return path_x, path_y
    except FileNotFoundError:
        print(f"파일 찾을 수 없음")
        return None, None

def visualize_all_paths():
    obstacles = load_obstacles()
    if obstacles is None:
        return

    path_files = sorted(glob.glob("path_*.txt"))

    if not path_files:
        print("파일을 찾을 수 없음")
        return

    print("시각화:", path_files)

    fig, ax = plt.subplots(figsize=(12, 12))
    ax.set_title("Path Planning Algorithm Comparison", fontsize=16)

    # 장애물 그리기
    for obs in obstacles:
        left, top, right, bottom = obs
        rect = patches.Rectangle(
            (left - 0.5, top - 0.5), right - left + 1, bottom - top + 1,
            linewidth=1, edgecolor='black', facecolor='darkgray', zorder=2
        )
        ax.add_patch(rect)

    colors = ['dodgerblue', 'limegreen', 'red', 'purple', 'orange']
    linestyles = ['-', '--', ':', '-.']
    
    has_drawn_start_goal = False

    for i, file_path in enumerate(path_files):
        path_x, path_y = load_path(file_path)
        if not path_x:
            continue


        try:
            algo_name = file_path.split('_')[1].split('.')[0]
            if algo_name == 'D': label = 'Dijkstra'
            elif algo_name == 'A': label = 'A*'
            elif algo_name == 'R': label = 'RRT*'
            else: label = algo_name
        except IndexError:
            label = file_path

        # 경로 그리기
        ax.plot(path_x, path_y,
                color=colors[i % len(colors)],
                linestyle=linestyles[i % len(linestyles)],
                linewidth=2.5,
                label=f"Path ({label})",
                zorder=3 + i)

        # 시작점과 도착점은 한 번만 그리기
        if not has_drawn_start_goal:
            ax.plot(path_x[0], path_y[0], marker='o', markersize=15, color='gold', label="Start/Goal", zorder=10, mec='black')
            ax.plot(path_x[-1], path_y[-1], marker='o', markersize=15, color='gold', zorder=10, mec='black')
            has_drawn_start_goal = True
            
    # 그래프 스타일 설정
    ax.set_xlabel("X coordinate")
    ax.set_ylabel("Y coordinate")
    ax.set_xticks(range(1, 21))
    ax.set_yticks(range(1, 21))
    ax.set_xlim(0.5, 20.5)
    ax.set_ylim(0.5, 20.5)
    ax.set_aspect('equal', adjustable='box')
    ax.grid(True, which='both', linestyle='--', linewidth=0.5)
    ax.legend(fontsize=12)
    
    plt.show()

if __name__ == '__main__':
    visualize_all_paths()
    input("\n시각화 완료. Enter 키를 누르면 종료") 
