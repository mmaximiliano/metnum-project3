from util import comparar
import sys, os
from string import Template
import matplotlib.pyplot as plt

noise_list = [0, 0.01, 0.1, 0.5, 3, 10, 80]

images = [
	{
		'file': 'tomo',
		'realSize': 100,
		'sizes': [5, 10, 25, 50],
    'e': lambda s:0
	}, {
		'file': 'tomo2',
		'realSize': 549,
		'sizes': [10, 20, 36, 60, 90, 135],
    'e': lambda s:s*s
	}, {
		'file': 'tomo3',
		'realSize': 452,
		'sizes': [10, 18, 30, 50, 75, 90],
    'e': lambda s:s*s
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

results = Template(("../experimentacion/outputs/noise/${image}/results/"
                    "reconstruccion-n_${size}_rayType_${ray_type}_rayN_${ray_param}_e_${e}_noise_${noise}.csv"))
imageDir = Template("../data-csv/${image}-${size}.csv")
graphDir = Template("noise/${image}/")
mkdirCommand = Template("mkdir -p ${dir}")

def main(argc, argv):
  for image in images:
    os.system(mkdirCommand.substitute(dir=graphDir.substitute(image=image['file'])))
    lines = []
    fig = plt.figure()
    for j, size in enumerate(image['sizes'], start=1):
      p = plt.subplot(2, len(image['sizes']) / 2, j)
      for ray in rays:
        psnrs = []
        noisePlot = []
        for noise in noise_list:
          resFile = results.substitute(image=image['file'], size=size, ray_type=ray['type'],
                                       ray_param=ray['param'](image['realSize'], size), noise=noise, e=image['e'](size))
          if not os.path.isfile(resFile):
            #print(resFile)
            continue
          psnr = comparar(imageDir.substitute(image=image['file'], size=size), resFile)['psnr']
          psnrs.append(float(psnr))
          noisePlot.append(noise)
        lines.append(p.plot(noisePlot, psnrs, label=ray['type'])[0])
      p.set_title('Tamaño: ' + str(size))
      p.set_xlabel('Ruido')
      p.set_ylabel('PSNR')
    fig.legend(lines, map(lambda x: x['name'], rays),loc='upper center', 
               bbox_to_anchor=(0, -0.933,1,1), ncol=4)
    plt.suptitle('PSNR en función del ruido para ' + image['file'])
    plt.tight_layout(rect=[0, 0.03, 1, 0.95])
    plt.savefig(graphDir.substitute(image=image['file']) + 'noise_graph.png')
    plt.clf()

	


if __name__ == '__main__':
    main(len(sys.argv), sys.argv)