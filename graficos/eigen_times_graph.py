from util import comparar
import sys, os
from string import Template
import matplotlib.pyplot as plt
from math import floor
import math
import json

eigens = [1, 0.9, 0.75, 0.5, 0.2]

images = [
	{
		'file': 'tomo',
		'realSize': 100,
		'sizes': [5, 10, 25, 50],
    'e': lambda e, s: floor(s * s * e)
	}
]

rays = [
	{
		'name': "random",
		'type': 0,
		'param': lambda realSize, s: s * s * 2
	},
	{
		'name': "lateralBorders",
		'type': 2,
		# 6 * realSize^2 / param = s * s * 2 <=>3 * realSize^2/s * s = param
		'param': lambda realSize, s: 3 * realSize * realSize//(s * s)
	},
	{
		'name': "allBorders",
		'type': 3,
		# 12 * realSize^2 / param = s * s * 2 <=> 6 * realSize^2 / (s * s) = param
		'param': lambda realSize, s: 6 * realSize * realSize//(s * s)
	},
]

results = Template(("../experimentacion/outputs/eigens-time/${image}/times-${iteration}/"
                    "times-n_${size}_rayType_${ray_type}_rayN_${ray_param}_e_${e}_noise_0.1.json"))
graphDir = Template("eigens-time/${image}/")
graphFile = "noise_graph.png"
mkdirCommand = Template("mkdir -p ${dir}")

def promedio(size, ray_type, ray_param, e, image):
  res = 0
  for i in range(20):
    with open(results.substitute(iteration=i, image=image, size=size, ray_type=ray_type, ray_param=ray_param, e=e)) as f:
      data = json.load(f)
      res += data['calculate_cml']
  return math.sqrt(res)

def main(argc, argv):
  for image in images:
    os.system(mkdirCommand.substitute(dir=graphDir.substitute(image=image['file'])))
    lines = []
    fig = plt.figure()
    for j, size in enumerate(image['sizes'], start=1):
      p = plt.subplot(2, 2, j)
      for i, ray in enumerate(rays, start=1):
        times = []
        eigenPlot = []
        for eigen in eigens:
          resFile = results.substitute(iteration=i, image=image['file'], size=size, ray_type=ray['type'],
                                       ray_param=ray['param'](image['realSize'], size),
                                       e=image['e'](eigen, size))
          if not os.path.isfile(resFile):
            print(resFile)
            continue
          time = promedio(image=image['file'], size=size, ray_type=ray['type'],
                          ray_param=ray['param'](image['realSize'], size),
                          e=image['e'](eigen, size))
          #print(time)
          times.append(int(time))
          eigenPlot.append(eigen)
        lines.append(p.plot(eigenPlot, times, label=ray['type'])[0])
      p.set_title('Tamaño: ' + str(size))
      p.set_xlabel('porcentaje de cantidad de VS')
      p.set_ylabel('Tiempo (sqrt Ms)')
    fig.legend(lines, [r['name'] for r in rays],loc='upper center', 
                bbox_to_anchor=(0, -0.933,1,1), ncol=4)
    plt.suptitle('Tiempo vs. el porcentaje de cantidad de VS para ' + image['file'])
    plt.tight_layout(rect=[0, 0.03, 1, 0.95])
    plt.savefig(graphDir.substitute(image=image['file']) + graphFile)
    plt.clf()

	


if __name__ == '__main__':
    main(len(sys.argv), sys.argv)