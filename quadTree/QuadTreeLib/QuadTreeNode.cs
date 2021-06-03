using System;
using System.Collections.Generic;
using System.Drawing;
using System.Diagnostics;

namespace QuadTreeLib
{
    public class QuadTreeNode<T> where T : IHasRect
    {
        public QuadTreeNode(RectangleF bounds)
        {
            m_bounds = bounds;
        }
		
        RectangleF m_bounds;

        List<T> m_contents = new List<T>();

        List<QuadTreeNode<T>> m_nodes = new List<QuadTreeNode<T>>(4);

        public bool IsEmpty { get { return m_bounds.IsEmpty || m_nodes.Count == 0; } }

        public RectangleF Bounds { get { return m_bounds; } }

        public int Count
        {
            get
            {
                int count = 0;

                foreach (QuadTreeNode<T> node in m_nodes)
                    count += node.Count;

                count += this.Contents.Count;

                return count;
            }
        }

        public List<T> SubTreeContents
        {
            get
            {
                List<T> results = new List<T>();

                foreach (QuadTreeNode<T> node in m_nodes)
                    results.AddRange(node.SubTreeContents);

                results.AddRange(this.Contents);
                return results;
            }
        }

        public List<T> Contents { get { return m_contents; } }

        public List<T> Query(RectangleF queryArea)
        {
            List<T> results = new List<T>();

            foreach (T item in this.Contents)
            {
                if (queryArea.IntersectsWith(item.Rectangle))
                    results.Add(item);
            }

            foreach (QuadTreeNode<T> node in m_nodes)
            {
                if (node.IsEmpty)
                    continue;

                if (node.Bounds.Contains(queryArea))
                {
                    results.AddRange(node.Query(queryArea));
                    break;
                }

                if (queryArea.Contains(node.Bounds))
                {
                    results.AddRange(node.SubTreeContents);
                    continue;
                }
				
                if (node.Bounds.IntersectsWith(queryArea))
                {
                    results.AddRange(node.Query(queryArea));
                }
            }


            return results;
        }

        public void Insert(T item)
        {
            if (!m_bounds.Contains(item.Rectangle))
            {
                Trace.TraceWarning("feature is out of the bounds of this quadtree node");
                return;
            }

            if (m_nodes.Count == 0)
                CreateSubNodes();

            foreach (QuadTreeNode<T> node in m_nodes)
            {
                if (node.Bounds.Contains(item.Rectangle))
                {
                    node.Insert(item);
                    return;
                }
            }
			
            this.Contents.Add(item);
        }

        public void ForEach(QuadTree<T>.QTAction action)
        {
            action(this);

            foreach (QuadTreeNode<T> node in this.m_nodes)
                node.ForEach(action);
        }

        private void CreateSubNodes()
        {
            if ((m_bounds.Height * m_bounds.Width) <= 10)
                return;

            float halfWidth = (m_bounds.Width / 2f);
            float halfHeight = (m_bounds.Height / 2f);

            m_nodes.Add(new QuadTreeNode<T>(new RectangleF(m_bounds.Location, new SizeF(halfWidth, halfHeight))));
            m_nodes.Add(new QuadTreeNode<T>(new RectangleF(new PointF(m_bounds.Left, m_bounds.Top + halfHeight), new SizeF(halfWidth, halfHeight))));
            m_nodes.Add(new QuadTreeNode<T>(new RectangleF(new PointF(m_bounds.Left + halfWidth, m_bounds.Top), new SizeF(halfWidth, halfHeight))));
            m_nodes.Add(new QuadTreeNode<T>(new RectangleF(new PointF(m_bounds.Left + halfWidth, m_bounds.Top + halfHeight), new SizeF(halfWidth, halfHeight))));
        }

    }
}
