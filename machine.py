#variables
nameToWrite = "shapes.xml"
panelsWide = 26 #19 #with half panels #28 #23
panelsHigh = 6
 #in pixels, must be recaclulated per resolution
panelSize = 125 #95 #130
panelTex = 125
panelGap =  7  #7
panelSplit = 21 #panelGap *7
panelSplitSmall = 15
panelOffset = 0

#shorthand xml tags
rS = "<root>\n"
rE = "</root>\n"
sS = "\t<shape id=\""
sM = "\">\n\t\t<setting key=\"type\">quad</setting>\n"
sE = "\t</shape>\n"
vS = "\t\t<outputVertices>\n"
vE = "\t\t</outputVertices>\n"
pS = "\t\t<inputPolygon>\n"
pE = "\t\t</inputPolygon>\n"
dS = "\t\t\t<vertex x=\""
dM = "\" y=\""
dE = "\"></vertex>\n"

#init and add preamble
idCounter = 0
toWrite = rS

#loop over quads 
for i in range( panelsHigh ):
  for j in range( panelsWide ) :
    toWrite += sS + str(idCounter) + sM + vS
    #projection verts
    if i < 2:
        toWrite += dS + str(j*panelSize + j*panelGap) +dM+ str(i*panelSize + i*panelGap) + dE
        toWrite += dS + str(j*panelSize + panelSize + j*panelGap) +dM+ str(i*panelSize + i*panelGap) + dE
        toWrite += dS + str(j*panelSize + panelSize + j*panelGap) +dM+ str(i*panelSize + panelSize + i*panelGap) + dE
        toWrite += dS + str(j*panelSize + j*panelGap) +dM+ str(i*panelSize + panelSize + i*panelGap) + dE
    elif i < 5:
        toWrite += dS + str(j*panelSize + j*panelGap) +dM+ str(i*panelSize + i*panelGap + panelSplit) + dE
        toWrite += dS + str(j*panelSize + panelSize + j*panelGap) +dM+ str(i*panelSize + i*panelGap + panelSplit) + dE
        toWrite += dS + str(j*panelSize + panelSize + j*panelGap) +dM+ str(i*panelSize + panelSize + i*panelGap + panelSplit) + dE
        toWrite += dS + str(j*panelSize + j*panelGap) +dM+ str(i*panelSize + panelSize + i*panelGap + panelSplit) + dE
    else:
        toWrite += dS + str(j*panelSize + j*panelGap) +dM+ str(i*panelSize + i*panelGap + panelSplit + panelSplitSmall) + dE
        toWrite += dS + str(j*panelSize + panelSize + j*panelGap) +dM+ str(i*panelSize + i*panelGap + panelSplit + panelSplitSmall) + dE
        toWrite += dS + str(j*panelSize + panelSize + j*panelGap) +dM+ str(i*panelSize + panelSize + i*panelGap + panelSplit + panelSplitSmall) + dE
        toWrite += dS + str(j*panelSize + j*panelGap) +dM+ str(i*panelSize + panelSize + i*panelGap + panelSplit + panelSplitSmall) + dE

    toWrite += vE + pS
    #texture verts
    toWrite += dS + str(j*panelTex) + dM + str(i*panelTex) + dE
    toWrite += dS + str(j*panelTex + panelTex) + dM + str(i*panelTex) + dE
    toWrite += dS + str(j*panelTex + panelTex) + dM + str(i*panelTex + panelTex) + dE
    toWrite += dS + str(j*panelTex) + dM + str(i*panelTex + panelTex) + dE

    toWrite += pE + sE
    idCounter += 1

#add post everything
toWrite += rE

fileOut = open( nameToWrite, "w" )
fileOut.write( toWrite )
fileOut.close()