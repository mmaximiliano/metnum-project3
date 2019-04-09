import os

# Ejemplo de uso:
#
# from util import comparar
# comparar('../data-csv/phantom-16.csv', '../resultados/phantom/random-sin-ruido/reconstruccion-16-0.csv')
def comparar(image1, image2):
	outTempFile = 'temp.txt'
	os.system("../codigo/build/compare " + image1 + " " + image2 + "> " + outTempFile)

	res = {}
	with open(outTempFile) as f:
		f.readline() # Salteo mensaje
		ecmLine = f.readline().strip().split()
		res['ecm'] = ecmLine[1]
		psnrLine = f.readline().strip().split()
		res['psnr'] = psnrLine[1]
		reqmiqrLine = f.readline().strip().split()
		res['reqmiqr'] = reqmiqrLine[1]

	return res
