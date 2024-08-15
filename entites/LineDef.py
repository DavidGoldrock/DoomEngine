class LineDef:
    def __init__(self, startVertex, endVertex, flags, sType, sTag, fSideDef, bSideDef, blocksPM, blocksM, ts, upperTextureUnpegged, lowerTextureUnpegged, secret, blocksSound, neverAutoMap, alwaysAutoMap):
        self.startVertex = startVertex
        self.endVertex = endVertex
        self.flags = flags
        self.sType = sType
        self.sTag = sTag
        self.fSideDef = fSideDef
        self.bSideDef = bSideDef
        self.blocksPM = blocksPM
        self.blocksM = blocksM
        self.ts = ts
        self.upperTextureUnpegged = upperTextureUnpegged
        self.lowerTextureUnpegged = lowerTextureUnpegged
        self.secret = secret
        self.blocksSound = blocksSound
        self.neverAutoMap = neverAutoMap
        self.alwaysAutoMap = alwaysAutoMap

    def __str__(self):
        return f"{self.startVertex=}, {self.endVertex=}, {self.flags=}, {self.sType=}, {self.sTag=}, {self.fSideDef=}, {self.bSideDef=}, {self.blocksPM=}, {self.blocksM=}, {self.ts=}, {self.upperTextureUnpegged=}, {self.lowerTextureUnpegged=}, {self.secret=}, {self.blocksSound=}, {self.neverAutoMap=}, {self.alwaysAutoMap= }"

    __repr__ = __str__
