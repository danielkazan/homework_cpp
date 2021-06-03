using System;
using System.Drawing;
using System.Collections.Generic;
using System.Diagnostics;

namespace QuadTreeLib
{
    public class QuadTree<T> where T : IHasRect
    {
        QuadTreeNode<T> m_root;

        RectangleF m_rectangle;

        public delegate void QTAction(QuadTreeNode<T> obj);

        public QuadTree(RectangleF rectangle)
        {
            m_rectangle = rectangle;
            m_root = new QuadTreeNode<T>(m_rectangle);
        }
		
        public int Count { get { return m_root.Count; } }

        public void Insert(T item)
        {
            m_root.Insert(item);
        }

        public List<T> Query(RectangleF area)
        {
            return m_root.Query(area);
        }
        
        public void ForEach(QTAction action)
        {
            m_root.ForEach(action);
        }

    }

}
