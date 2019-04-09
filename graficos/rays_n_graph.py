from util import comparar
import sys, os
from string import Template
import matplotlib.patches as mpatches
import matplotlib.pyplot as plt
from math import floor

noise_list = [0.01, 0.1, 0.5]
r_params = [2, 3, 4]

colors = ['red', 'green', 'brown', 'blue', 'magenta', 'orange']

images = [
	{
		'file': 'tomo',
		'realSize': 100,
		'sizes': [5, 10, 25, 50],
    'e': lambda s:0
	}, {
		'file': 'tomo2',
		'realSize': 540,
		'sizes': [10, 20, 36, 60, 90, 135],
    'e': lambda s: s*s
	}, {
		'file': 'tomo3',
		'realSize': 450,
		'sizes': [10, 18, 30, 50, 75, 90],
    'e': lambda s:s*s
	}
]

rays = [
	{
		'name': "random",
		'type': 0,
		'param': lambda realSize, s, r_param: s * s * r_param
	},
	{
		'name': "rotated",
		'type': 1,
		# quiero 4 * realSize/param = s*s*2 <=> 2 * realSize/s*s = param
		'param': lambda realSize, s, r_param: (r_param * realSize//(s*s)) if (r_param * realSize//(s*s) > 0) else 1
	},
	{
		'name': "lateralBorders",
		'type': 2,
		# 6 * realSize^2 / param = s * s * 2 <=>3 * realSize^2/s * s = param
		'param': lambda realSize, s, r_param: r_param * 3/2 * realSize * realSize//(s * s)
	},
	{
		'name': "allBorders",
		'type': 3,
		# 12 * realSize^2 / param = s * s * 2 <=> 6 * realSize^2 / (s * s) = param
		'param': lambda realSize, s, r_param: r_param * 3 * realSize * realSize//(s * s)
	},
]

results = Template(("../experimentacion/outputs/n_rays/${image}/results/"
                    "reconstruccion-n_${size}_rayType_${ray_type}_rayN_${ray_param}_e_${e}_noise_${noise}.csv"))
imageDir = Template("../data-csv/${image}-${size}.csv")
graphDir = Template("ray_params/${image}/")
graphFile = Template("noise_graph_${noise}.png")
mkdirCommand = Template("mkdir -p ${dir}")

def main(argc, argv):
  for image in images:
    handles = []
    for i, size in enumerate(image['sizes']):
      handles.append(mpatches.Patch(color=colors[i], label=str(size)))
    image['handles'] = handles

  for image in images:
    os.system(mkdirCommand.substitute(dir=graphDir.substitute(image=image['file'])))
    for noise in noise_list:
      lines = []
      fig = plt.figure()
      defLines = []
      for i, ray in enumerate(rays, start=1):
        p = plt.subplot(2, 2, i)
        for j, size in enumerate(image['sizes'], start=1):
          psnrs = []
          paramList = []
          for param in r_params:
            resFile = results.substitute(image=image['file'], size=size, ray_type=ray['type'],
                                        ray_param=int(ray['param'](image['realSize'], size, param)), noise=noise,
                                        e=image['e'](size))
            if not os.path.isfile(resFile):
              print(resFile)
              continue
            psnr = comparar(imageDir.substitute(image=image['file'], size=size), resFile)['psnr']
            psnrs.append(float(psnr))
            paramList.append(param)
          lines.append(p.plot(paramList, psnrs, label=ray['type'], color=colors[j-1])[0])
        p.set_title('Rayo: ' + str(ray['name']))
        p.set_xlabel('Cantidad de rayos')
        p.set_ylabel('PSNR')
        defLines = lines if len(lines) > len(defLines) else defLines
      fig.legend(handles=image['handles'],loc='upper center', 
                 bbox_to_anchor=(0, -0.933,1,1), ncol=len(image['handles']))
      plt.suptitle('PSNR vs. la cantidad rayos para ' + image['file'] + ' con ruido ' + str(noise))
      plt.tight_layout(rect=[0, 0.03, 1, 0.95])
      plt.savefig(graphDir.substitute(image=image['file']) + graphFile.substitute(noise=noise))
      plt.clf()

	


if __name__ == '__main__':
    main(len(sys.argv), sys.argv)