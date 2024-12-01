import copy

def removeLeftRecursion(rulesDiction):
    store = {}
    for lhs in rulesDiction:
        alphaRules = []
        betaRules = []
        allrhs = rulesDiction[lhs]
        
        for subrhs in allrhs:
            if subrhs[0] == lhs:
                alphaRules.append(subrhs[1:])
            else:
                betaRules.append(subrhs)
        
        if len(alphaRules) != 0:
            lhs_ = lhs + "'"
            while (lhs_ in rulesDiction.keys()) or (lhs_ in store.keys()):
                lhs_ += "'"
            
            for b in range(len(betaRules)):
                betaRules[b].append(lhs_)
            
            rulesDiction[lhs] = betaRules
            
            for a in range(len(alphaRules)):
                alphaRules[a].append(lhs_)
            alphaRules.append(['0'])
            store[lhs_] = alphaRules
        
    for left in store:
        rulesDiction[left] = store[left]
    return rulesDiction


def LeftFactoring(rulesDiction):
    newDict = {}
    for lhs in rulesDiction:
        allrhs = rulesDiction[lhs]
        temp = dict()

        for subrhs in allrhs:
            if subrhs[0] not in list(temp.keys()):
                temp[subrhs[0]] = [subrhs]
            else:
                temp[subrhs[0]].append(subrhs)
        
        new_rule = []
        tempo_dict = {}

        for term_key in temp:
            allStartingWithTermKey = temp[term_key]
            
            if len(allStartingWithTermKey) > 1:
                lhs_ = lhs + "'"
                while (lhs_ in rulesDiction.keys()) or (lhs_ in tempo_dict.keys()):
                    lhs_ += "'"
                
                new_rule.append([term_key, lhs_])
                ex_rules = []
                for g in temp[term_key]:
                    ex_rules.append(g[1:])
                tempo_dict[lhs_] = ex_rules
            else:
                new_rule.append(allStartingWithTermKey[0])
        
        newDict[lhs] = new_rule
        for key in tempo_dict:
            newDict[key] = tempo_dict[key]
    
    return newDict


def first(rule):
    global diction, firsts
    if len(rule) != 0 and rule is not None:
        if rule[0] in term_userdef:
            return [rule[0]]
        elif rule[0] == '0':
            return ['0']
        if len(rule) != 0:
            if rule[0] in list(diction.keys()):
                fres = []
                rhs_rules = diction[rule[0]]
                for itr in rhs_rules:
                    indivRes = first(itr)
                    if '0' in indivRes:
                        indivRes.remove('0')
                    if len(rule) > 1:
                        ansNew = first(rule[1:])
                        if ansNew is not None:
                            if type(ansNew) is list:
                                indivRes += ansNew
                            else:
                                indivRes.append(ansNew)
                    if type(indivRes) is list:
                        fres.extend(indivRes)
                    else:
                        fres.append(indivRes)
                return fres


def follow(nt):
    global start_symbol, diction, firsts, follows
    solset = set()
    
    if nt == start_symbol:
        solset.add('$')
    
    for curNT in diction:
        rhs = diction[curNT]
        for subrule in rhs:
            if nt in subrule:
                index_nt = subrule.index(nt)
                subrule = subrule[index_nt + 1:]
                
                if len(subrule) != 0:
                    res = first(subrule)
                    if '0' in res:
                        res.remove('0')
                    if len(subrule) > 1:
                        res += first(subrule[1:])
                    res.append('0')
                    solset.update(res)
                else:
                    if nt != curNT:
                        res = follow(curNT)
                        if res is not None:
                            solset.update(res)
    return list(solset)


def computeAllFirsts():
    global diction, firsts
    for rule in rules:
        k = rule.split("->")
        k[0] = k[0].strip()
        k[1] = k[1].strip()
        rhs = k[1]
        multirhs = rhs.split('|')
        
        for i in range(len(multirhs)):
            multirhs[i] = multirhs[i].strip()
            multirhs[i] = multirhs[i].split()
        
        diction[k[0]] = multirhs
    
    diction = removeLeftRecursion(diction)
    diction = LeftFactoring(diction)
    
    for y in list(diction.keys()):
        t = set()
        for sub in diction.get(y):
            res = first(sub)
            if res != None:
                if type(res) is list:
                    t.update(res)
                else:
                    t.add(res)
        firsts[y] = t


def computeAllFollows():
    global start_symbol, diction, firsts, follows
    for NT in diction:
        solset = set()
        sol = follow(NT)
        if sol is not None:
            solset.update(sol)
        follows[NT] = solset


def createParseTable():
    import copy
    global diction, firsts, follows, term_userdef
    mx_len_first = 0
    mx_len_fol = 0
    
    for u in diction:
        k1 = len(str(firsts[u]))
        k2 = len(str(follows[u]))
        
        if k1 > mx_len_first:
            mx_len_first = k1
        if k2 > mx_len_fol:
            mx_len_fol = k2
    
    print(f"{{:<{10}}} {{:<{mx_len_first + 5}}} {{:<{mx_len_fol + 5}}}".format("Non-T", "FIRST", "FOLLOW"))
    
    for u in diction:
        print(f"{{:<{10}}} {{:<{mx_len_first + 5}}} {{:<{mx_len_fol + 5}}}".format(u, str(firsts[u]), str(follows[u])))
    
    ntlist = list(diction.keys())
    terminals = copy.deepcopy(term_userdef)
    terminals.append('$')
    mat = []
    
    for x in diction:
        row = []
        for y in terminals:
            row.append('')
        mat.append(row)
    
    grammar_is_LL = True
    for lhs in diction:
        rhs = diction[lhs]
        for y in rhs:
            res = first(y)
            if '0' in res:
                if type(res) == str:
                    res = [res]
                res.remove('0')
                res += follows[lhs]
            
            if type(res) is str:
                res = [res]
            
            for c in res:
                if c in terminals:
                    xnt = ntlist.index(lhs)
                    yt = terminals.index(c)
                    if mat[xnt][yt] == '':
                        mat[xnt][yt] = f"{lhs} -> {' '.join(y)}"
                    else:
                        if f"{lhs} -> {' '.join(y)}" in mat[xnt][yt]:
                            continue
                        else:
                            grammar_is_LL = False
                            mat[xnt][yt] += f", {lhs} -> {' '.join(y)}"
    
    print("\nGenerated parsing table:\n")
    frmt = "{:>12}" * len(terminals)
    print(frmt.format(*terminals))
    
    j = 0
    for y in mat:
        frmt1 = "{:>12}" * len(y)
        print(f"{ntlist[j]} {frmt1.format(*y)}")
        j += 1
    
    return (mat, grammar_is_LL, terminals)


rules = [
    "E -> T E'",
    "E' -> + T E' | 0",
    "T -> F T'",
    "T' -> * F T' | 0",
    "F -> ( E ) | id"
]

term_userdef = ['id', '+', '*', '(', ')']
diction = {}
firsts = {}
follows = {}

computeAllFirsts()
start_symbol = list(diction.keys())[0]
computeAllFollows()

(parsing_table, result, tabTerm) = createParseTable()
