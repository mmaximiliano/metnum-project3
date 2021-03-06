import sys, os
from string import Template
from math import floor

r_params = [1,5, 2, 3, 4]

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

command = Template(("../codigo/build/tp3 "
  "-i ${image} -s ${s} -n ${n} "
  "-r ${ray_type} ${ray_param} -e ${e} "
  "-o ${results_dir} -t ${time_dir}"))
resultsDir = Template("outputs/n_rays-time/${image}/results")
timeDir = Template("outputs/n_rays-time/${image}/times-${num}")
imageDir = Template("../data-csv/${image}.csv")
mkdirCommand = Template("mkdir -p ${dir}")

def main(argc, argv):
  for t in images:
    for it in range(20):
      os.system(mkdirCommand.substitute(dir=resultsDir.substitute(image=t['file'])))
      os.system(mkdirCommand.substitute(dir=timeDir.substitute(image=t['file'], num=it)))

      for s in t['sizes']:
        for r_param in r_params:
          for r in rays:
            d = {
              'image': imageDir.substitute(image=t['file']),
              's': s,
              'n': 0.1,
              'ray_type': r['type'],
              'ray_param': r['param'](t['realSize'], s, r_param),
              'e': s*s,
              'results_dir': resultsDir.substitute(image=t['file']),
              'time_dir': timeDir.substitute(image=t['file'], num=it)
            }
            print("Corriendo imagen ", t['file'], " con size ", s, " y rayos ", r['name'])
            print(command.safe_substitute(d))
            os.system(command.safe_substitute(d))


if __name__ == '__main__':
    main(len(sys.argv), sys.argv)