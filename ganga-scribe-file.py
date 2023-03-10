#file for writing out ganga jobs

#Eliot Walton 9/3/23

##########################################
##########################################

#For writing out ganga jobs

j = jobs(287)

f = open("MC-file-list.txt", "w")

lines = []

for sj in j.subjobs:
	if sj.status=='completed':
		df = sj.outputfiles[0]
		url = df.accessURL()
		lines.append(url[0])
f.write('\n'.join(lines))
f.close()

#########################################
#########################################

#If job is stuck in completing

j = jobs(288)
for sj in j.subjobs:
	if sj.status=='completing':
		sj.backend.reset()

#########################################
#########################################
