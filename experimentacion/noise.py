import sys, os
from string import Template

noise_list = [0, 0.01, 0.1, 0.5, 3, 10, 80]

images = [
	{
		'file': 'tomo',
		'realSize': 100,
		'sizes': [5, 10, 25, 50]
	}, {
		'file': 'tomo2',
		'realSize': 540,
		'sizes': [10, 20, 36, 60, 90, 135]
	}, {
		'file': 'tomo3',
		'realSize': 450,
		'sizes': [10, 18, 30, 50, 75, 90]
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

command = Template(("../codigo/build/tp3 "
	"-i ${image} -s ${s} -n ${n} "
	"-r ${ray_type} ${ray_param} -e 0 "
	"-o ${results_dir} -t ${time_dir} -c ${cache_dir}"))
resultsDir = Template("outputs/noise/${image}/results")
timeDir = Template("outputs/noise/${image}/times")
cacheDir = Template("outputs/noise/${image}/cache")
imageDir = Template("../data-csv/${image}.csv")
mkdirCommand = Template("mkdir -p ${dir}")

def main(argc, argv):
	for t in images:
		os.system(mkdirCommand.substitute(dir=resultsDir.substitute(image=t['file'])))
		os.system(mkdirCommand.substitute(dir=timeDir.substitute(image=t['file'])))
		os.system(mkdirCommand.substitute(dir=cacheDir.substitute(image=t['file'])))

		for s in t['sizes']:
			for	n in noise_list:
				for r in rays:
					d = {
						'image': imageDir.substitute(image=t['file']),
						's': s,
						'n': n,
						'ray_type': r['type'],
						'ray_param': r['param'](t['realSize'], s),
						'results_dir': resultsDir.substitute(image=t['file']),
						'time_dir': timeDir.substitute(image=t['file']),
						'cache_dir': cacheDir.substitute(image=t['file'])
					}
					print("Corriendo imagen ", t['file'], " con size ", s, ", ruido ", n, " y rayos ", r['name'])
					print(command.safe_substitute(d))
					os.system(command.safe_substitute(d))


if __name__ == '__main__':
    main(len(sys.argv), sys.argv)