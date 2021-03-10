import networkx as nx
import random
import matplotlib.pyplot as plt
import collections
import time

#Algorithme de propagation de label sur le graphe g
def label_propagation(g):
	
	start_time = time.time()
	l=0
	i=0
	for i in nx.nodes(g):
		g.nodes[i]['label'] = l
		l+=1
		
	finish = False
	rnodes = list(range(nx.number_of_nodes(g)))
	temp = 0
	while finish == False:
		for i in range(len(rnodes)-2):
			j = random.randint(0,i)
			temp = rnodes[j]
			rnodes[j] = rnodes[i] 
			rnodes[i] = temp	
		for i in rnodes:
			labels = []
			for k in nx.neighbors(g,i):
				labels.append(g.nodes[k]['label'])
	
			newlabel = collections.Counter(labels).most_common(1)
			if newlabel[0][0] == g.nodes[i]['label']:
				finish = True
			else:
				g.nodes[i]['label'] = newlabel[0][0]
				finish = False
	print("--Propagation : 	%ss --" % (time.time() - start_time))				





# ~ Algorithme de k-means pris à l'adresse si dessous
# ~ https://stackoverflow.com/questions/62902871/how-can-i-cluster-a-graph-g-created-in-networkx


def k_means(G,k):
	
	nx.draw(G,with_labels = True,node_color='b',node_size=500);

	from node2vec import Node2Vec
	# Generate walks
	node2vec = Node2Vec(G, dimensions=2, walk_length=20, num_walks=10,workers=4)
	#Learn embeddings 
	model = node2vec.fit(window=10, min_count=1)
	#model.wv.most_similar('1')
	model.wv.save_word2vec_format("embedding.emb") #save the embedding in file embedding.emb
	
	from sklearn.cluster import KMeans
	import numpy as np


	X = np.loadtxt("embedding.emb", skiprows=1) # load the embedding of the nodes of the graph
	#print(X)
	# sort the embedding based on node index in the first column in X
	X=X[X[:,0].argsort()]; 
	#print(X)
	Z=X[0:X.shape[0],1:X.shape[1]]; # remove the node index from X and save in Z
	start_time = time.time()
	kmeans = KMeans(n_clusters=k, random_state=0).fit(Z) # apply kmeans on Z
	labels=kmeans.labels_  # get the cluster labels of the nodes.
	
	print("--K-means : 	%ss --" % (time.time() - start_time))
	return labels
	
#attribut une couleur à chaque noeuds de g en fonction de leur label	
def color_map_generator(g):
	color_map = []
	cluster = {}
	for i in nx.nodes(g):
		l = g.nodes[i]['label'] 
		if l in cluster:
			color_map.append(cluster[l])
		else:
			r = random.random()
			v = random.random()
			b = random.random()
			cluster[l] = (r,v,b)
			color_map.append(cluster[l])
	return color_map
	

p=1
while p != 0 :
	
	print('p? ')
	p = float(input())
	if p!=0:	
		print('q? ')
		q = float(input())
		while q>p:
			print('q? ')
			q = float(input())

		#création de g
		k = 400
		g = nx.Graph()
		g.add_nodes_from(range(k))
		for i in range(k):
			for j in range(i,k):
				if i//(k//4) == j//(k//4):
					if random.random()<p:
						g.add_edge(i,j)
						
				else:
					if random.random()<q:
						g.add_edge(i,j)
				
		
			
		label_propagation(g)
		color_map_propa = color_map_generator(g)
		
					
		cluster = k_means(g,4)
		for i in nx.nodes(g):
			g.nodes[i]['label'] = cluster[i]
			
		color_map_kmeans = color_map_generator(g)	



		
		
		
		
		pos = nx.spring_layout(g)

		plt.subplot(121)
		nx.draw(g,node_color = color_map_propa,node_size = 250)
		plt.title("label propagation" + ' \np='+str(p)+'    q='+str(q))
		
		plt.subplot(122)
		nx.draw(g,node_color = color_map_kmeans,node_size = 250)
		plt.title("k-means" + '\np='+str(p)+'    q='+str(q))
		plt.show()
		
		# ~ nx.draw(g,node_size = 250)
		# ~ plt.title('p='+str(p)+'    q='+str(q))
		# ~ plt.show()
