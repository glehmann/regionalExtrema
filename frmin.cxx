// a test routine for regional extrema using flooding
#include "itkRegionalMinimaImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkCommand.h"
#include <itkIntensityWindowingImageFilter.h>
#include "itkCommand.h"

template < class TFilter >
class ProgressCallback : public itk::Command
{
public:
  typedef ProgressCallback   Self;
  typedef itk::Command  Superclass;
  typedef itk::SmartPointer<Self>  Pointer;
  typedef itk::SmartPointer<const Self>  ConstPointer;

  itkTypeMacro( IterationCallback, Superclass );
  itkNewMacro( Self );

  /** Type defining the optimizer. */
  typedef    TFilter     FilterType;

  /** Method to specify the optimizer. */
  void SetFilter( FilterType * filter )
    {
    m_Filter = filter;
    m_Filter->AddObserver( itk::ProgressEvent(), this );
    }

  /** Execute method will print data at each iteration */
  void Execute(itk::Object *caller, const itk::EventObject & event)
    {
    Execute( (const itk::Object *)caller, event);
    }

  void Execute(const itk::Object *, const itk::EventObject & event)
    {
    std::cout << m_Filter->GetNameOfClass() << ": " << m_Filter->GetProgress() << std::endl;
    }

protected:
  ProgressCallback() {};
  itk::WeakPointer<FilterType>   m_Filter;
};





int main(int, char * argv[])
{
  const int dim = 2;
  
  typedef unsigned char PType;
  typedef itk::Image< PType, dim > IType;

  typedef float RType;
  typedef itk::Image< RType, dim > IRType;

  typedef itk::ImageFileReader< IType > ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[2] );

  typedef itk::RegionalMinimaImageFilter< IType, IType > FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( reader->GetOutput() );
  filter->SetFullyConnected( atoi(argv[1]) );

  typedef itk::ImageFileWriter< IType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( filter->GetOutput() );
  writer->SetFileName( argv[3] );
  writer->Update();



  // do the same with a real type image
  typedef itk::IntensityWindowingImageFilter< IType, IRType > RescaleType;
  RescaleType::Pointer rescale = RescaleType::New();
  rescale->SetInput( reader->GetOutput() );
  rescale->SetWindowMinimum( itk::NumericTraits< PType >::Zero );
  rescale->SetWindowMaximum( itk::NumericTraits< PType >::max() );
  rescale->SetOutputMaximum( 1.0f );
  rescale->SetOutputMinimum( -1.0f );

  typedef itk::RegionalMinimaImageFilter< IRType, IType > RFilterType;
  RFilterType::Pointer rfilter = RFilterType::New();
  rfilter->SetInput( rescale->GetOutput() );
  rfilter->SetFullyConnected( atoi(argv[1]) );

  typedef ProgressCallback< RFilterType > ProgressType;
  ProgressType::Pointer progress = ProgressType::New();
  progress->SetFilter( rfilter );

  WriterType::Pointer writer2 = WriterType::New();
  writer2->SetInput( rfilter->GetOutput() );
  writer2->SetFileName( argv[4] );
  writer2->Update();

  return 0;
}

