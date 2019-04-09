from util import comparar
import sys, os
from string import Template
import matplotlib.pyplot as plt
from math import floor

noise_list = [0.01, 0.1, 0.5]

eigens = [1, 0.9, 0.75, 0.5, 0.2]

images = [
	{
		'file': 'tomo',
		'realSize': 100,
		'sizes': [5, 10, 25, 50],
    'e': lambda e, s: floor(s * s * e)
	}, {
		'file': 'tomo2',
		'realSize': 540,
		'sizes': [10, 20, 36, 60],
    'e': lambda e, s: floor(s * s * e)
	}, {
		'file': 'tomo3',
		'realSize': 450,
		'sizes': [10, 18, 30],
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
		'name': "rotated",
		'type': 1,
		# quiero 4 * realSize/param = s*s*2 <=> 2 * realSize/s*s = param
		'param': lambda realSize, s: (2 * realSize//(s*s)) if (2 * realSize//(s*s) > 0) else 1
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

results = Template(("../experimentacion/outputs/eigens/${image}/results/"
                    "reconstruccion-n_${size}_rayType_${ray_type}_rayN_${ray_param}_e_${e}_noise_${noise}.csv"))
imageDir = Template("../data-csv/${image}-${size}.csv")
graphDir = Template("eigens/${image}/")
graphFile = Template("noise_graph_${noise}.png")
mkdirCommand = Template("mkdir -p ${dir}")

def main(argc, argv):
  for image in images:
    os.system(mkdirCommand.substitute(dir=graphDir.substitute(image=image['file'])))
    for noiseIt, noise in enumerate(noise_list, start=1):
      lines = []
      fig = plt.figure()
      for i, ray in enumerate(rays, start=1):
        p = plt.subplot(2, 2, i)
        for j, size in enumerate(image['sizes'], start=1):
          psnrs = []
          eigenPlot = []
          for eigen in eigens:
            resFile = results.substitute(image=image['file'], size=size, ray_type=ray['type'],
                                        ray_param=ray['param'](image['realSize'], size), noise=noise,
                                        e=image['e'](eigen, size))
            if not os.path.isfile(resFile):
              #print(resFile)
              continue
            psnr = comparar(imageDir.substitute(image=image['file'], size=size), resFile)['psnr']
            psnrs.append(float(psnr))
            eigenPlot.append(eigen)
          lines.append(p.plot(eigenPlot, psnrs, label=ray['type'])[0])
        p.set_title('Rayo: ' + str(ray['name']))
        p.set_xlabel('porcentaje de cantidad de VS')
        p.set_ylabel('PSNR')
      fig.legend(lines, image['sizes'],loc='upper center', 
                 bbox_to_anchor=(0, -0.933,1,1), ncol=4)
      plt.suptitle('PSNR vs. el porcentaje de cantidad de VS para ' + image['file'] + ' con ruido ' + str(noise))
      plt.tight_layout(rect=[0, 0.03, 1, 0.95])
      plt.savefig(graphDir.substitute(image=image['file']) + graphFile.substitute(noise=noiseIt))
      plt.clf()

	


if __name__ == '__main__':
    main(len(sys.argv), sys.argv)