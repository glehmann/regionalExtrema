#ifndef __itkValuedRegionalMaximaImageFilter_h
#define __itkValuedRegionalMaximaImageFilter_h

#include "itkValuedRegionalExtremaImageFilter.h"
#include "itkNumericTraits.h"

namespace itk {

template <class TInputImage, class TOutputImage>
class ITK_EXPORT ValuedRegionalMaximaImageFilter :
    public
    ValuedRegionalExtremaImageFilter<TInputImage, TOutputImage,
			       std::greater<typename TInputImage::PixelType>,
			       std::greater<typename TOutputImage::PixelType>  >
{
public:
  typedef ValuedRegionalMaximaImageFilter Self;
  typedef ValuedRegionalExtremaImageFilter<TInputImage, TOutputImage,
				     std::greater<typename TInputImage::PixelType>,
				     std::greater<typename TOutputImage::PixelType> > Superclass;

  typedef SmartPointer<Self>   Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);


protected:
  ValuedRegionalMaximaImageFilter() 
  {
    SetMarkerValue(NumericTraits<typename TOutputImage::PixelType>::NonpositiveMin());
  }
  virtual ~ValuedRegionalMaximaImageFilter() {}

private:
  ValuedRegionalMaximaImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented



}; // end ValuedRegionalMaximaImageFilter

} //end namespace itk
#endif
