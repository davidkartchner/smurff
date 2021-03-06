from .wrapper import TrainSession

class SmurffSession(TrainSession):
    def __init__(self, Ytrain, priors, Ytest = None, side_info = None, **args):
        TrainSession.__init__(self, priors = priors, **args)
        self.addTrainAndTest(Ytrain, Ytest)

        if side_info is not None:
            assert len(side_info) == self.nmodes
            for mode in range(self.nmodes):
                si = side_info[mode]
                if si is not None:
                    self.addSideInfo(mode, si)

class MacauSession(SmurffSession):
    def __init__(self,  Ytrain, Ytest = None, side_info = None, univariate = False, **args):
        nmodes = len(Ytrain.shape)
        priors = ['normal'] * nmodes

        if side_info is not None:
            assert len(side_info) == nmodes
            for d in range(nmodes):
                if side_info[d] is not None:
                    priors[d] = 'macau'

        if univariate:
            priors = [ p + "one" for p in priors ]

        SmurffSession.__init__(self, Ytrain, priors, Ytest, side_info,  **args)
 
class BPMFSession(MacauSession):
    def __init__(self, Ytrain, Ytest = None, univariate = False, **args):
         MacauSession.__init__(self, Ytrain, Ytest, None, univariate, **args)

class GFASession(SmurffSession):
    def __init__(self, Views, Ytest = None, **args):
        Ytrain = Views[0]
        nmodes = len(Ytrain.shape)
        assert nmodes == 2
        priors = ['normal', 'spikeandslab']

        TrainSession.__init__(self, priors = priors, **args)
        self.addTrainAndTest(Ytrain, Ytest)

        for p in range(1, len(Views)):
            self.addData([0,p], Views[p])

# old API -- for compatibility reasons

def smurff(*args, **kwargs):
    return SmurffSession(*args, **kwargs).run()

def bpmf(*args, **kwargs):
    return BPMFSession(*args, **kwargs).run()

def macau(*args, **kwargs):
    return MacauSession(*args, **kwargs).run()

def gfa(*args, **kwargs):
    return GFASession(*args, **kwargs).run()
